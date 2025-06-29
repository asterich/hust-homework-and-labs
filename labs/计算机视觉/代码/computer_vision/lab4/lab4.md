## 实验四：卷积神经网络可解释性分析

### Grad-CAM

本次实验中，我尝试复现了 Grad-CAM。相较于它的前辈 CAM，它不需要原模型后面接 GAP 层，不需要对模型进行修改，生成的热力图也更精细。实验代码和结果在 `lab4_gradcam.ipynb` 中。

#### 实现过程

首先，我们查看 AlexNet 的网络结构：

```python
AlexNet(
  (features): Sequential(
    (0): Conv2d(3, 64, kernel_size=(11, 11), stride=(4, 4), padding=(2, 2))
    (1): ReLU(inplace=True)
    (2): MaxPool2d(kernel_size=3, stride=2, padding=0, dilation=1, ceil_mode=False)
    (3): Conv2d(64, 192, kernel_size=(5, 5), stride=(1, 1), padding=(2, 2))
    (4): ReLU(inplace=True)
    (5): MaxPool2d(kernel_size=3, stride=2, padding=0, dilation=1, ceil_mode=False)
    (6): Conv2d(192, 384, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1))
    (7): ReLU(inplace=True)
    (8): Conv2d(384, 256, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1))
    (9): ReLU(inplace=True)
    (10): Conv2d(256, 256, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1))
    (11): ReLU(inplace=True)
    (12): MaxPool2d(kernel_size=3, stride=2, padding=0, dilation=1, ceil_mode=False)
  )
  (avgpool): AdaptiveAvgPool2d(output_size=(6, 6))
  (classifier): Sequential(
    (0): Dropout(p=0.5, inplace=False)
    (1): Linear(in_features=9216, out_features=4096, bias=True)
    (2): ReLU(inplace=True)
    (3): Dropout(p=0.5, inplace=False)
    (4): Linear(in_features=4096, out_features=4096, bias=True)
    (5): ReLU(inplace=True)
    (6): Linear(in_features=4096, out_features=2, bias=True)
  )
)
```

我们发现最后一层卷积层在 `features[10]` 处。我们先定义两个钩子函数，然后把它注册在这一层中：

```python
def backward_hook(module, grad_in, grad_out):
    def hook(grad):
        gradients.append(grad_out[0].detach())
    grad_out.register_hook(hook)
        

def forward_hook(module, input, output):
    activations.append(output)


model.features[10].register_forward_hook(forward_hook)
model.features[10].register_forward_hook(backward_hook)
```

需要注意的一点是，由于后面的 ReLU 层是 inplace 的，`features[10]` 不能 `register_backward_hook`，只能通过一种比较间接的方式，用 `register_forward_hook` 去注册。

接下来就是跑模型，我们需要先前向传播一次再反向传播一次，让钩子获得梯度和激活特征：

```python
# forward
output = model(img)
max_idx = np.argmax(output.data.numpy())
print("cat" if max_idx == 0 else "dog")

# backward
model.zero_grad()
class_loss = output[0, max_idx]	
class_loss.backward()

# grads
grads_val = gradients[0].data.numpy().squeeze()
activation = activations[0].data.numpy().squeeze()
```

最后需要展示 Grad-CAM 热力图。但是我们没有现成的热力图，只有梯度和激活特征。编写如下函数，然后用它来计算、展示特征图和热力图：

```python
def cam_show_img(img, activation, grads, W, H):
    print("activation map:")
    for i in range(activation.shape[0] // 16):
        plt.figure(figsize=(60, 4))
        for j in range(0, 16):
            ax = plt.subplot(1, 16, j + 1)
            ax.set_xticks([])
            ax.set_yticks([])
            activation_vis = np.uint8(255 * activation[i * 16 + j])
            plt.imshow(np.uint8(activation_vis), cmap='gray')
        plt.show()


    print("cam:")
    cam = np.zeros(activation.shape[1: ], dtype=np.float32)
    grads = grads.reshape([grads.shape[0], -1])
    weights = np.mean(grads, axis=1)	
    print(weights.shape)
    print(activation.shape)
    for i, w in enumerate(weights):
        cam += w * activation[i, :, :]
    cam = np.maximum(cam, 0)
    cam = cam / cam.max()
    print(cam.shape)
    cam = cv2.resize(cam, (W, H))

    heatmap = cv2.applyColorMap(np.uint8(255 * cam), cv2.COLORMAP_JET)
    heatmap = cv2.cvtColor(heatmap, cv2.COLOR_BGR2RGB)

    cam_img = 0.5 * heatmap + 0.5 * img

    plt.imshow(np.uint8(cam_img))
    plt.show()

# show cam
cam_show_img(raw_img, activation, grads_val, W, H)
```

#### 结果

![Alt text](out/gradcam/image.png)

![Alt text](out/gradcam/image-1.png)

![Alt text](out/gradcam/image-2.png)

### LayerCAM

这一节复现 LayerCAM，具体实现和实验结果在 `lab4_layercam.ipynb` 中。

#### 实现过程

与上一节不同，我决定用一个类封装 LayerCAM。下面是这个类的实现：

```python
class LayerCAM(object):

    def __init__(self, model, target_layer):
        self.model = model
        self.model.eval()
        if torch.cuda.is_available():
          self.model.cuda()
        self.gradients = []
        self.activations = []

        def backward_hook(module, grad_in, grad_out):
            def hook(grad):
                self.gradients.append(grad_out[0].detach())
            grad_out.register_hook(hook)
            

        def forward_hook(module, input, output):
            self.activations.append(output)

        target_layer.register_forward_hook(forward_hook)
        target_layer.register_forward_hook(backward_hook)


    def forward(self, input, class_idx=None, retain_graph=False):
        b, c, h, w = input.size()
        
        # predication on raw input
        logit = self.model(input)
        
        if class_idx is None:
            predicted_class = logit.max(1)[-1]
        else:
            predicted_class = torch.LongTensor([class_idx])
        
        one_hot_output = torch.FloatTensor(1, logit.size()[-1]).zero_()
        one_hot_output[0][predicted_class] = 1
        # Zero grads
        self.model.zero_grad()
        # Backward pass with specified target
        logit.backward(gradient=one_hot_output.cuda(), retain_graph=True)
        activations = self.activations[0].clone().detach()
        gradients = self.gradients[0].clone().detach()
        b, k, u, v = activations.size()
        
        with torch.no_grad():
            activation_maps = activations * F.relu(gradients)
            cam = torch.sum(activation_maps, dim=1).unsqueeze(0)    
            cam_min, cam_max = cam.min(), cam.max()
            norm_cam = (cam - cam_min).div(cam_max - cam_min + 1e-8).data

        return norm_cam, activations

    def __call__(self, input, class_idx=None, retain_graph=False):
        return self.forward(input, class_idx, retain_graph)
```

可以看到，注册钩子的流程也是一样的，不同之处在于 `forward` 函数。这里需要把激活特征图乘上梯度的 ReLU。

接下来是绘图函数。由于热力图已经在 forward 一步生成，我们只需要对它做一些尺寸变换就可以生成可视化的结果：

```python
def cam_show_img(img, cam, activations):
    if activations is not None:
        print("activation map:")
        activations = activations[0]
        for i in range(activations.shape[0] // 16):
            plt.figure(figsize=(60, 4))
            for j in range(0, 16):
                ax = plt.subplot(1, 16, j + 1)
                ax.set_xticks([])
                ax.set_yticks([])
                activation_vis = np.uint8(255 * activations[i * 16 + j])
                plt.imshow(np.uint8(activation_vis), cmap='gray')
            plt.show()

    cam = cam[0]
    # print(cam.shape)
    (H, W, channel) = img.shape
    cam = cv2.resize(cam.transpose(1, 2, 0), (W, H))

    heatmap = cv2.applyColorMap(np.uint8(255 * cam), cv2.COLORMAP_JET)
    heatmap = cv2.cvtColor(heatmap, cv2.COLOR_BGR2RGB)

    cam_img = 0.5 * heatmap + 0.5 * img

    plt.imshow(np.uint8(cam_img))
    plt.show()
```

#### 结果

LayerCAM热力图和各通道特征图的可视化见 `lab4_layercam.ipynb`
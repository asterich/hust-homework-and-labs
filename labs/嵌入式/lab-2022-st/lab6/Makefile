EXENAME := 
EXESRCS := gomoku_draw.c gomoku_board.c button.c gomoku_game.c board_interact.c gomoku_ai.c

include ../common/rules.mk

gomoku_server: $(EXEOBJS) gomoku_server.c
	$(CC) $(LDFLAGS) -o gomoku_server $(EXEOBJS) gomoku_server.c  $(LIB)
	mv gomoku_server ../out/

gomoku_client: $(EXEOBJS) gomoku_client.c
	$(CC) $(LDFLAGS) -o gomoku_client $(EXEOBJS) gomoku_client.c  $(LIB)
	mv gomoku_client ../out/

gomoku_1p_with_ai: $(EXEOBJS) gomoku_1p_with_ai.c
	$(CC) $(LDFLAGS) -o gomoku_1p_with_ai $(EXEOBJS) gomoku_1p_with_ai.c  $(LIB)
	mv gomoku_1p_with_ai ../out/
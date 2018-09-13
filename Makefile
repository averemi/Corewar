MAKE	=	@make

.PHONY: all clean fclean re
all:
	@make -C VM
	@make -C assembler
	cp assembler/asm .
	cp VM/corewar .
clean:
	$(MAKE) clean -C VM
	$(MAKE) clean -C assembler

fclean: clean
	$(MAKE) fclean -C VM && rm -f corewar
	$(MAKE) fclean -C assembler && rm -f asm

re: fclean all

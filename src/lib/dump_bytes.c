void        dump_byte(unsigned char byte)
{
  unsigned char i;

  for (i = 0; i < 8; i++)
    kputchar(kb & (1 << i) + 48);
  kputchar('\n');
}

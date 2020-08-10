BEGIn
  VAR INT number, sum;
  sum:=0;
  READ(number);
  WHILE number<>0 DO
    sum:=sum+number;
    READ(number)
  OD;
  WRITE(sum);
END.


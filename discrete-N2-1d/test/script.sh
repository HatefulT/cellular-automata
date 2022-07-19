
cp ../build/main.out ./

for n in {1..255};
do 
  echo -e "512\n512\n$n" | ./main.out > /dev/null
  cp output.bmp "outputs/$n.bmp"
done

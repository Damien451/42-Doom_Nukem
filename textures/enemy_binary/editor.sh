rm -f enemy.bin;
touch enemy.bin;
for i in `seq 1 21`;
do
	cat enemy$i.binary >> enemy.bin;
done

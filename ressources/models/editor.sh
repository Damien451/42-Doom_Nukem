rm -f enemy.bin;
touch enemy.bin;
for i in `seq 0 19`;
do
	cat $i.binary >> models.bin;
done

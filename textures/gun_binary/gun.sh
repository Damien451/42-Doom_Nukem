rm -f gun.bin;
touch gun.bin;
for i in `seq 1 16`;
do
	cat gun$i.binary >> gun.bin;
done

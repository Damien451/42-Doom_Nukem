rm -f editor.bin;
touch editor.bin;
for i in `seq 0 41`;
do
	cat $i.binary >> editor.bin;
done
for i in `seq 42 62`;
do
	cat $i.binary >> editor.bin;
	cat $i.binary >> editor.bin;
	cat $i.binary >> editor.bin;
	cat $i.binary >> editor.bin;
done

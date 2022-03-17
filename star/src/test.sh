cd ..

make clean
make

# 1 archive
cd src/
rm out.star
../bin/star archive ../bin ./out.star

# 2 list
../bin/star list ./out.star

# 3 Extract Mode
../bin/star extract ./out.star

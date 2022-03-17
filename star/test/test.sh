# 1 archive
rm out.star
../bin/star archive ../bin ./out.star

# 2 list
../bin/star list ./out.star

# 3 Extract Mode
rm -r bin/
../bin/star extract ./out.star

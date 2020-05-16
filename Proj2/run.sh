make | grep !" ";
#echo "Testing Venancio"
#Venancio
#for i in outros\ testes/Venancio/tes*;do printf "Test: %s:$i " ; ./a.out<"$i"; done >out; 
#sed 's/outros testes\///g' out >ou1;
#diff ou1 outros\ testes/Venancio/OutParaNelson.out;
#echo "Testing Major"
#Major
#for i in outros\ testes/Major/*;do printf "Test: " ; ./a.out<"$i"; done >out
#for i in outros\ testes/Major/*;do printf "Test: " ; tail --lines=1 "$i"; done >outO; diff out outO
echo "Testing Oliveira"
#Oliveira
for i in outros\ testes/Oliveira/test/*;do printf "Test: " ;./a.out<"$i"; done >out
for i in outros\ testes/Oliveira/res/*;do printf "Test: " ;cat "$i"; done >outO; diff --side-by-side out outO

rm out outO ou1

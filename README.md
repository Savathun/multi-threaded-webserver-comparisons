# multi-threaded-webserver-comparisons

- install apache bench (apache lounge, includes bench, for windows dl link: [link](https://www.apachelounge.com/download/VS16/binaries/httpd-2.4.53-win64-VS16.zip))
- extract zip; run executable `Apache24/bin/ab` 
- specific command I use, for the go code:  
```shell
.\ab -n 10000 -c 100 localhost/ > go/ab.txt
"====================================================" >> go/ab.txt
.\ab -n 10000 -c 200 localhost/ >> go/ab.txt
```

- for drill: 
```shell
drill --benchmark benchmark-1000.yml --stats -q > rust/drill.txt
"====================================================" >> rust/drill.txt
drill --benchmark benchmark-2000.yml --stats -q >> rust/drill.txt
```

whole thing on linux (set dir first): 
```shell
dir="
```

```shell
ab -n 10000 -c 100 localhost/ > $dir/ab.txt
echo "====================================================" >> $dir/ab.txt
ab -n 10000 -c 200 localhost/ >> $dir/ab.txt
drill --benchmark benchmark-1000.yml --stats -q > $dir/drill.txt
echo "====================================================" >> $dir/drill.txt
drill --benchmark benchmark-2000.yml --stats -q >> $dir/drill.txt
wrk -t8 -c500 -d30s http://localhost > $dir/wrk.txt
```

g++ -o webserver webserver.cpp -I$BOOST_ROOT -I. -L$BOOST_ROOT/stage/lib -lboost_system -pthread



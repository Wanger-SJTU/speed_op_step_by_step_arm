
ori_path=$1

adb push $ori_path /data/local/tmp/main
adb shell "cd /data/local/tmp/ && chmod +x main && ./main"

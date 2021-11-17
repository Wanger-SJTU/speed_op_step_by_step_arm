
ori_path=$1

adb push $ori_path /data/main
adb shell "cd /data/ && chmod +x main && ./main"

#!/system/bin/sh
#
#
#
#
#
target=`getprop ro.board.platform`
case "$target" in
    # QSD8x50: Passion, Bravo, Supersonic, Inc
    "qsd8k")
        # Cpu Governor
        echo "ondemand" > /sys/devices/system/cpu/cpu0/cpufreq/scaling_governor
        # CpuGovernorService
        chown system /sys/devices/system/cpu/cpufreq/ondemand/sampling_rate
        chown system /sys/devices/system/cpu/cpufreq/ondemand/io_is_busy
        # Tune for scorpion
        echo 245000 > /sys/devices/system/cpu/cpu0/cpufreq/scaling_min_freq
        echo 998400 > /sys/devices/system/cpu/cpu0/cpufreq/scaling_max_freq
        echo 50000 > /sys/devices/system/cpu/cpufreq/ondemand/sampling_rate
        echo 90 > /sys/devices/system/cpu/cpufreq/ondemand/up_threshold
        echo 1 > /sys/devices/system/cpu/cpufreq/ondemand/io_is_busy
        echo 4 > /sys/devices/system/cpu/cpufreq/ondemand/sampling_down_factor
        # /system/lib/libqct-opt JNI native will write
        # mfreq to set CPU freq to max for performance
        chown root.system /sys/devices/system/cpu/mfreq
        chmod 220 /sys/devices/system/cpu/mfreq
        # Configure and enable KSM
        echo 1000 > /sys/kernel/mm/ksm/sleep_millisecs
        echo 100 > /sys/kernel/mm/ksm/pages_to_scan
        echo 1 > /sys/kernel/mm/ksm/run
    ;;
esac

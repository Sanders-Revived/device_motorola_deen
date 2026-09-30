#!/vendor/bin/sh
carrier=$(getprop ro.carrier)
[ -z "$carrier" ] && carrier=$(getprop ro.boot.carrier)
[ -z "$carrier" ] && carrier=$(getprop ro.vendor.carrier)
carrier=$(echo "$carrier" | tr '[:upper:]' '[:lower:]')

case "$carrier" in
    amxbr|tefbr|timbr|retbr)
        path=/vendor/etc/acdbdata/brazil
        ;;
    *)
        path=/vendor/etc/acdbdata/common
        ;;
esac

index=0
for file in "$path"/*.acdb; do
    [ -e "$file" ] || continue
    setprop "persist.vendor.audio.calfile$index" "$file"
    index=$((index + 1))
done

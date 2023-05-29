a=(300 100 500 200 400)

IFS=$'\n' sorted=($(sort <<<"${a[*]}")); unset IFS
printf "[%s]\n" "${sorted[@]}"


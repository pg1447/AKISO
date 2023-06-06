find $1* -type f -printf '%s.' -exec md5sum {} \;  | sort -r | cut -d. -f 2 | uniq -w 32 -d

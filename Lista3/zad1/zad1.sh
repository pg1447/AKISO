cat $1 | sort | uniq | cat>uniq1
cat $2 | sort | uniq | cat>uniq2

echo SUMA MNOGOSCIOWA:
cat uniq1 uniq2 | sort | uniq
echo ROZNICA MNOGOSCIOWA:
cat uniq1 uniq2 | sort | uniq -d | cat>iloczyn
cat uniq1 iloczyn | sort | uniq -u
rm iloczyn uniq1 uniq2

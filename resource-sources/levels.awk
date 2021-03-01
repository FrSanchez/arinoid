#!/usr/local/bin/awk -f

/level[0-9]+/ { match($0, /level[0-9]+/); print ",{//", substr($0, RSTART, RLENGTH) }
/^[0-9]/ { gsub(/^/, "{"); gsub(/,$/,"},"); gsub(/[0-9]$/,"&}}");  print }
#! /bin/sed -f

# These are all the naming changes taking place in the first effort to bring
# consistency to the naming of things in my library. Hopefully this 'patch'
# can be applied to projects using the lib.

# sxc_string.h, sxc_string.c, tests
s/String_defaults/sxc_string_defaults/g
s/String/struct sxc_string/g
s/STRING/SXC_STRING/g

# sxc_utils.h, sxc_utils.c, tests
s/charcounts/cc/g
s/charcount/sxc_charcount/g
s/Charcount/sxc_charcount/g
s/SXC_Charset/sxc_charset/g
s/charmap/sxc_charmap/g
s/Charmap/sxc_charmap/g


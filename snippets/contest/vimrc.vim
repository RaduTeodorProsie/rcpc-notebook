" Name: Vimrc
" Description: Type into `~/.vimrc`. F5 saves, compiles the current
"   file with sanitizers and, only if that worked, runs it on the
"   file `in`; F6 does the same reading the keyboard. To check a
"   typed snippet, select its lines (`V`, then move) and press
"   `\h`: it prints the snippet's 6-character hash. Needs
"   `hash.sh` in the current folder. `(` and `[` close at once;
"   `{` then Enter closes the brace on its own line.
set nu ai cin et ts=2 sw=2 sts=2 mouse=a is hls ru
sy on
let c = '!g++ -std=c++20 -g -Wall -fsanitize=address,'
  \ . 'undefined % -o %:r && ./%:r'
map <F5> :w<CR>:exe c . ' < in'<CR>
map <F6> :w<CR>:exe c<CR>
vmap <Leader>h :w !sh hash.sh<CR>
ino {<CR> {<CR>}<Esc>O
ino ( ()<Left>
ino [ []<Left>

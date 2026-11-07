" Name: Vimrc
" Description: `V`, select lines, `\h`: hash of the selection.
"   Brackets close themselves (see Setup).
set nu rnu ai cin et ts=4 sw=4 sts=4 mouse=a is hls ru
set notimeout ttimeout ttm=50
sy on
vmap <Leader>h :w !sh hash.sh<CR>
ino ( ()<Left>
ino [ []<Left>
ino { {}<Left>
ino {<CR> {<CR>}<Esc>O

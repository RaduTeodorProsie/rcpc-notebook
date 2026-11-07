// Name: Setup
#set list(spacing: 2.6pt, indent: 0pt, body-indent: 3pt, marker: [–])
- Vimrc into `~/.vimrc`, Bashrc at the end of `~/.bashrc`, then
  `source ~/.bashrc`; `hash.sh` into the working folder. Start
  `vim`, not `vi` (often vim-tiny: ignores half the vimrc).
- Check: `sh hash.sh template.cpp` prints Template's hash (needs
  GCC's `cpp`); `cs template.cpp && ./template` runs clean;
  in Vim, `:imap {` lists two mappings.
- `<Esc>O` ends in the letter O, not zero (with `0`, Enter after
  `{` leaves you in normal mode). `<CR>` etc. are typed literally.
- Never type `)`, `]`, `}`: step past with →, or `Esc` `j` `o`
  after a block. A typed one doubles and the hash fails.
- `{` shows only after the next key (`notimeout`; without it a
  pause before Enter gives `{}`, not a block).
- Before pasting into the terminal `:set paste`, then `:set nopaste`.

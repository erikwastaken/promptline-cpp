# powerline-cpp
A minimalist implementation of terminal powerline in modern C++

## How to use
Currently only supports zsh and bash.

Uses ANSI escape sequences.

Build the executable powerline-cpp via the Makefile. Requires C++20.

### zsh
Add the following to your .zshrc and replace [path/to/powerline-cpp/executable] with the corresponding path
```zsh
function powerline_precmd() {
    PS1=$([path/to/powerline-cpp/executable] "$?")
}

function install_powerline_precmd() {
  for s in "${precmd_functions[@]}"; do
    if [ "$s" = "powerline_precmd" ]; then
      return
    fi
  done
  precmd_functions+=(powerline_precmd)
}

if [ -f [path/to/powerline-cpp/executable] ]; then
    install_powerline_precmd
fi
```

### bash
Add the following to your .bashrc and replace [path/to/powerline-cpp/executable] with the corresponding path
```bash
function _update_prompt() {
    PS1="$([path/to/powerline-cpp/executable] "$?")"
}

if [ -f "[path/to/powerline-cpp/executable]" ]; then
    PROMPT_COMMAND="_update_prompt; $PROMPT_COMMAND"
fi
```

terminal-writer
================

Reads text from stdin and writes it to stdout like in old movies.

```bash
$ echo "Hello World" | tw 80s
```

To see all available modes run

```bash
$ tw help
```

```bash
terminal-writer - Reads text from stdin an writes it to stdout like in old movies.

tw [MODE]

Modes:

  80s        Print text like in old movies.
  80s-fast   Print text like in old movies, but a bit faster.
  human      Write like a real person.
  wc4        Like the mission screen in Wing Commander 4.
```

# Available modes

## 80s

Prints text like in old movies.

![80s](doc/80s.gif "80s mode")

## 80s-fast

Prints text like in old movies, but a bit faster.

![80s](doc/80s-fast.gif "80s-fast mode")

## human

Writes like a real person.

![80s](doc/human.gif "humam mode")

## wc4

Like the mission screen in Wing Commander 4.

![80s](doc/wc4.gif "wc4 mode")

# Build

Build the project with

```bash
$ make
```

Only standard libraries are used.
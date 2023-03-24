package main

import (
	"bufio"
	"fmt"
	"math/rand"
	"os"
	"time"
)

type mode struct {
	name             string
	description      string
	characterWaitMin int
	characterWaitMax int
	lineWaitMin      int
	lineWaitMax      int
}

func showHelp(modes map[string]mode) {
	fmt.Println("terminal-writer (golang) - Reads text from stdin an writes it to stdout like in old movies.")
	fmt.Println("terminal-writer [MODE]")
	fmt.Println("Modes:")

	for _, mode := range modes {
		fmt.Printf("  %-11s %s\n", mode.name, mode.description)
	}
}

func run(mode mode) {
	rand.Seed(time.Now().UnixNano())

	scanner := bufio.NewScanner(os.Stdin)
	for scanner.Scan() {
		for _, c := range scanner.Text() {
			fmt.Print(string(c))
			characterWait := rand.Intn(mode.characterWaitMax-mode.characterWaitMin) + mode.characterWaitMin
			time.Sleep(time.Duration(characterWait) * time.Millisecond)
		}

		lineWait := rand.Intn(mode.lineWaitMax-mode.lineWaitMin) + mode.lineWaitMin
		time.Sleep(time.Duration(lineWait) * time.Millisecond)
		fmt.Println()
	}
}

func main() {
	modes := make(map[string]mode)
	modes["human"] = mode{
		name:             "human",
		description:      "Writes like a real person.",
		characterWaitMin: 75,
		characterWaitMax: 375,
		lineWaitMin:      15,
		lineWaitMax:      675}
	modes["80s"] = mode{
		name:             "80s",
		description:      "Prints text like in old movies.",
		characterWaitMin: 5,
		characterWaitMax: 25,
		lineWaitMin:      15,
		lineWaitMax:      675}
	modes["80s-fast"] = mode{
		name:             "80s-fast",
		description:      "Prints text like in old movies, but a bit faster.",
		characterWaitMin: 5,
		characterWaitMax: 15,
		lineWaitMin:      15,
		lineWaitMax:      275}
	modes["wc4"] = mode{
		name:             "wc4",
		description:      "Like the mission screen in Wing Commander 4.",
		characterWaitMin: 45,
		characterWaitMax: 55,
		lineWaitMin:      45,
		lineWaitMax:      75}

	if len(os.Args) > 1 {
		cmd := os.Args[1]
		mode, exists := modes[cmd]
		if cmd == "help" {
			showHelp(modes)
		} else if exists {
			run(mode)
		} else {
			fmt.Println("Unknown mode: " + cmd)
			fmt.Println("See 'help' for more information.")
		}
	} else {
		fmt.Println("No mode given")
		fmt.Println("See 'help' for more information.")
	}

	os.Exit(0)
}

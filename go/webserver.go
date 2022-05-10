package main

import (
	"fmt"
	"log"
	"net/http"
)

func main() {
	http.HandleFunc("/", func(w http.ResponseWriter, r *http.Request) {
		fmt.Fprintf(w, "Hello")
	})
	// Start server on port 80, you can view it by going to "localhost" in your browser
	log.Fatal(http.ListenAndServe(":80", nil))
}

package main

import (
	"bufio"
	"fmt"
	"net"
	_ "net"
	"os"
	"strings"
)

func main() {

	scanner := bufio.NewScanner(os.Stdin)
	var site string

	fmt.Println("PhilliumWebserver...STARTING")
	fmt.Println("site file name: ")
	if scanner.Scan() {
		site = scanner.Text()
	}
	listener(site)
}
func listener(site string) {
	server, err := net.Listen("tcp", ":8080")
	if err != nil {
		fmt.Println(err)
	}
	defer server.Close()
	for {
		conn, err := server.Accept()
		if err != nil {
			fmt.Println(err)
			continue
		}
		go Ptcp(site, conn)
	}

}
func Ptcp(site string, conn net.Conn) {
	defer conn.Close()
	reader := bufio.NewReader(conn)
	writer := bufio.NewWriter(conn)
	for {
		mess, err := reader.ReadString('\n')
		if err != nil {
			fmt.Println(err)
			return
		}
		mess = strings.TrimSpace(mess)
		if mess == "Phill is Done?" {
			_, err := writer.WriteString("Oh yes,Phill is Done baby!\n")
			if err != nil {
				fmt.Println(err)
				return
			}
			//потом высылаем данные размера,имени  и сам .phill файл
			err = writer.Flush()
			if err != nil {
				fmt.Println(err)
				return
			}

		} else {
			conn.Close()
			break
		}

	}
}

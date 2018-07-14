esp8266_client:	esp8266_client.c
	gcc -o esp8266_client esp8266_client.c

clean:
	rm -f esp8266_client

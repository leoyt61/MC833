CLIENT_TARGET_PATH=./client/target
CLIENT_SRC_PATH=./client/src
CLIENT_SERVICES_PATH=./client/src/services
CLIENT_UTILS_PATH=./client/src/utils

DATA_PATH=./data

SERVER_TARGET_PATH=./server/target
SERVER_SRC_PATH=./server/src
SERVER_REPOSITORIES_PATH=./server/src/repositories
SERVER_MODELS_PATH=./server/src/models
SERVER_UTILS_PATH=./server/src/utils
SERVER_PORT=8080

all: client server

run-client: client
	${CLIENT_TARGET_PATH}/main

client: ${CLIENT_TARGET_PATH}/main ${CLIENT_TARGET_PATH}

${CLIENT_TARGET_PATH}/main: ${CLIENT_SRC_PATH}/main.c ${CLIENT_TARGET_PATH}/interface.o ${CLIENT_TARGET_PATH}
	gcc -o ${CLIENT_TARGET_PATH}/main ${CLIENT_SRC_PATH}/main.c ${CLIENT_TARGET_PATH}/common.o ${CLIENT_TARGET_PATH}/object.o ${CLIENT_TARGET_PATH}/pseudo_http.o ${CLIENT_TARGET_PATH}/movie_service.o ${CLIENT_TARGET_PATH}/interface.o 

${CLIENT_TARGET_PATH}/interface.o: ${CLIENT_SRC_PATH}/interface.c ${CLIENT_TARGET_PATH}/movie_service.o ${CLIENT_TARGET_PATH}
	gcc -o ${CLIENT_TARGET_PATH}/interface.o -c ${CLIENT_SRC_PATH}/interface.c

${CLIENT_TARGET_PATH}/movie_service.o: ${CLIENT_SERVICES_PATH}/movie_service.c ${CLIENT_TARGET_PATH}/pseudo_http.o ${CLIENT_TARGET_PATH}
	gcc -o ${CLIENT_TARGET_PATH}/movie_service.o -c ${CLIENT_SERVICES_PATH}/movie_service.c

${CLIENT_TARGET_PATH}/pseudo_http.o: ${CLIENT_UTILS_PATH}/pseudo_http.c ${CLIENT_TARGET_PATH}/common.o ${CLIENT_TARGET_PATH}/object.o ${CLIENT_TARGET_PATH}
	gcc -o ${CLIENT_TARGET_PATH}/pseudo_http.o -c ${CLIENT_UTILS_PATH}/pseudo_http.c

${CLIENT_TARGET_PATH}/object.o: ${CLIENT_UTILS_PATH}/object.c ${CLIENT_TARGET_PATH}
	gcc -o ${CLIENT_TARGET_PATH}/object.o -c ${CLIENT_UTILS_PATH}/object.c

${CLIENT_TARGET_PATH}/common.o: ${CLIENT_UTILS_PATH}/common.c ${CLIENT_TARGET_PATH}
	gcc -o ${CLIENT_TARGET_PATH}/common.o -c ${CLIENT_UTILS_PATH}/common.c

${CLIENT_TARGET_PATH}:
	mkdir -p ${CLIENT_TARGET_PATH}

zip-client: clean-client
	zip -r udp_client.zip ${CLIENT_SRC_PATH}/* Makefile

clean-client:
	rm -rf ${CLIENT_TARGET_PATH}/*

run-server: server
	${SERVER_TARGET_PATH}/main ${SERVER_PORT}

server: ${SERVER_TARGET_PATH}/main ${SERVER_TARGET_PATH}
	mkdir -p ${DATA_PATH}
	mkdir -p ${DATA_PATH}/movies

${SERVER_TARGET_PATH}/main: ${SERVER_SRC_PATH}/main.c ${SERVER_TARGET_PATH}/server.o ${SERVER_TARGET_PATH}
	gcc -o ${SERVER_TARGET_PATH}/main ${SERVER_SRC_PATH}/main.c ${SERVER_TARGET_PATH}/file_handler.o ${SERVER_TARGET_PATH}/common.o ${SERVER_TARGET_PATH}/request.o ${SERVER_TARGET_PATH}/response.o ${SERVER_TARGET_PATH}/movie.o ${SERVER_TARGET_PATH}/movie_txt_repository.o ${SERVER_TARGET_PATH}/use-cases.o ${SERVER_TARGET_PATH}/server.o

${SERVER_TARGET_PATH}/server.o: ${SERVER_SRC_PATH}/server.c ${SERVER_TARGET_PATH}/request.o ${SERVER_TARGET_PATH}/response.o ${SERVER_TARGET_PATH}/use-cases.o ${SERVER_TARGET_PATH}
	gcc -o ${SERVER_TARGET_PATH}/server.o -c ${SERVER_SRC_PATH}/server.c

${SERVER_TARGET_PATH}/use-cases.o: ${SERVER_SRC_PATH}/use-cases.c ${SERVER_TARGET_PATH}/request.o ${SERVER_TARGET_PATH}/response.o ${SERVER_TARGET_PATH}/movie_txt_repository.o ${SERVER_TARGET_PATH}
	gcc -o ${SERVER_TARGET_PATH}/use-cases.o -c ${SERVER_SRC_PATH}/use-cases.c

${SERVER_TARGET_PATH}/movie_txt_repository.o: ${SERVER_REPOSITORIES_PATH}/movie_txt_repository.c ${SERVER_TARGET_PATH}/movie.o ${SERVER_TARGET_PATH}/file_handler.o ${SERVER_TARGET_PATH}
	gcc -o ${SERVER_TARGET_PATH}/movie_txt_repository.o -c ${SERVER_REPOSITORIES_PATH}/movie_txt_repository.c

${SERVER_TARGET_PATH}/movie.o: ${SERVER_MODELS_PATH}/movie.c ${SERVER_TARGET_PATH}/common.o ${SERVER_TARGET_PATH}
	gcc -o ${SERVER_TARGET_PATH}/movie.o -c ${SERVER_MODELS_PATH}/movie.c

${SERVER_TARGET_PATH}/response.o: ${SERVER_UTILS_PATH}/response.c ${SERVER_TARGET_PATH}/request.o ${SERVER_TARGET_PATH}
	gcc -o ${SERVER_TARGET_PATH}/response.o -c ${SERVER_UTILS_PATH}/response.c

${SERVER_TARGET_PATH}/request.o: ${SERVER_UTILS_PATH}/request.c ${SERVER_TARGET_PATH}/common.o ${SERVER_TARGET_PATH}
	gcc -o ${SERVER_TARGET_PATH}/request.o -c ${SERVER_UTILS_PATH}/request.c

${SERVER_TARGET_PATH}/common.o: ${SERVER_UTILS_PATH}/common.c ${SERVER_TARGET_PATH}
	gcc -o ${SERVER_TARGET_PATH}/common.o -c ${SERVER_UTILS_PATH}/common.c

${SERVER_TARGET_PATH}/file_handler.o: ${SERVER_UTILS_PATH}/file_handler.c ${SERVER_TARGET_PATH}
	gcc -o ${SERVER_TARGET_PATH}/file_handler.o -c ${SERVER_UTILS_PATH}/file_handler.c

${SERVER_TARGET_PATH}:
	mkdir -p ${SERVER_TARGET_PATH}

zip-server: clean-server
	zip -r udp_server.zip ${SERVER_SRC_PATH}/* Makefile

clean-server:
	rm -rf ${SERVER_TARGET_PATH}/* ${DATA_PATH}

zip: clean
	zip -r udp.zip ${CLIENT_SRC_PATH}/* ${SERVER_SRC_PATH}/* Makefile

clean:
	rm -rf ${CLIENT_TARGET_PATH}/* ${SERVER_TARGET_PATH}/* ${DATA_PATH} *.zip

clean-db:
	rm -rf ${DATA_PATH}
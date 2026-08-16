FROM ubuntu:22.04 AS builder

RUN apt-get update && apt-get install -y --no-install-recommends \
    autoconf bison flex gcc g++ libprotobuf-dev libnl-route-3-dev libtool make pkg-config \
    ca-certificates protobuf-compiler perl git \
    libncurses-dev \
    ncurses-term \
    && rm -rf /var/lib/apt/lists/*

RUN git clone --branch 3.3 https://github.com/google/nsjail /nsjail
WORKDIR /nsjail
RUN make

WORKDIR /app
COPY Makefile magic_maze.c draw.h draw.c flag.txt start.sh ./
RUN make

FROM ubuntu:22.04

RUN apt-get update && apt-get install -y --no-install-recommends \
    libprotobuf-dev libnl-route-3-dev \
    libncurses-dev \
    ncurses-term \
    socat \
    && rm -rf /var/lib/apt/lists/*

COPY --from=builder /nsjail/nsjail /bin/nsjail
COPY --from=builder /app/magic_maze /app/magic_maze
COPY --from=builder /app/flag.txt /app/flag.txt
COPY --from=builder /app/start.sh /app/start.sh

RUN useradd -m challengeuser && chown -R challengeuser:challengeuser /app
RUN chmod +x /app/start.sh
WORKDIR /app
USER challengeuser

EXPOSE 9000

CMD socat TCP-LISTEN:9000,fork,reuseaddr,linger=0 EXEC:"/app/start.sh",pty,setsid,sigint,sane

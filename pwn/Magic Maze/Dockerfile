# Stage 1: Build stage - build nsjail and challenge program from source
FROM ubuntu:22.04 AS builder

# Install all build dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    autoconf bison flex gcc g++ libprotobuf-dev libnl-route-3-dev libtool make pkg-config \
    ca-certificates protobuf-compiler perl git \
    libncurses-dev \
    ncurses-term \
    && rm -rf /var/lib/apt/lists/*

# Build nsjail
RUN git clone https://github.com/google/nsjail /nsjail
WORKDIR /nsjail
RUN make

# Build challenge program
WORKDIR /app
COPY Makefile magic_maze.c draw.h draw.c flag.txt start.sh ./
RUN make

# Stage 2: Runtime stage - minimal image with only needed binaries and files
FROM ubuntu:22.04

# Install only runtime dependencies needed by nsjail and challenge binary
RUN apt-get update && apt-get install -y --no-install-recommends \
    libprotobuf-dev libnl-route-3-dev \
    libncurses-dev \
    ncurses-term \
    socat \
    && rm -rf /var/lib/apt/lists/*

# Copy binaries and necessary files from builder stage
COPY --from=builder /nsjail/nsjail /bin/nsjail
COPY --from=builder /app/magic_maze /app/magic_maze
COPY --from=builder /app/flag.txt /app/flag.txt
COPY --from=builder /app/start.sh /app/start.sh

# Create and use a non-root user
RUN useradd -m challengeuser && chown -R challengeuser:challengeuser /app
RUN chmod +x /app/start.sh
WORKDIR /app
USER challengeuser

# Expose port for nsjail
EXPOSE 9000


# Elle crée un faux terminal (pty) et lance le script start.sh
#CMD socat TCP-LISTEN:9000,fork,reuseaddr EXEC:"/app/start.sh",pty,setsid,sigint,sane
# Ajout de ",linger=0" dans la partie TCP-LISTEN
CMD socat TCP-LISTEN:9000,fork,reuseaddr,linger=0 EXEC:"/app/start.sh",pty,setsid,sigint,sane

# Stage 1: Build stage
FROM ubuntu:22.04 AS builder

RUN apt-get update && apt-get install -y --no-install-recommends \
    autoconf bison flex gcc g++ libprotobuf-dev libnl-route-3-dev libtool make pkg-config \
    ca-certificates protobuf-compiler perl git && rm -rf /var/lib/apt/lists/*

RUN git clone https://github.com/google/nsjail /nsjail
WORKDIR /nsjail
RUN make

WORKDIR /app
COPY Makefile draconophobia.c flag.txt ./
RUN make

# Stage 2: Runtime stage
FROM ubuntu:22.04

RUN apt-get update && apt-get install -y --no-install-recommends \
    libprotobuf-dev libnl-route-3-dev && rm -rf /var/lib/apt/lists/*

COPY --from=builder /nsjail/nsjail /bin/nsjail
COPY --from=builder /app/draconophobia /app/draconophobia
COPY --from=builder /app/flag.txt /app/flag.txt

# Create and use a non-root user
RUN useradd -m challengeuser && chown -R challengeuser:challengeuser /app
WORKDIR /app
USER challengeuser

# Expose port for nsjail
EXPOSE 9000

# Run nsjail to sandbox the challenge program
CMD nsjail \
  -Ml --port 9000 \
  --user nobody \
  --group nogroup \
  -R /dev/urandom \
  -R /app/flag.txt \
  -R /app/draconophobia \
  -R /lib -R /lib64 -R /usr/lib -R /usr/local/lib \
  --chroot /app \
  -- /app/draconophobia \

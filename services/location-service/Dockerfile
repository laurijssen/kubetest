FROM python:3.8-slim-buster
LABEL description="Run container location service"

RUN apt-get update && apt-get install -y gcc python3-dev python3-pip zlib1g-dev g++ unixodbc-dev

RUN pip3 install --no-cache pyodbc grpcio google-api-python-client

RUN mkdir -p /proto
COPY proto/*.py /proto/
COPY location_grpc.py /
COPY __main__.py /

CMD [ "python3", "/__main__.py" ] 
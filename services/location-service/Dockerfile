FROM python:3.8-slim-buster
LABEL description="Run container location service"

RUN apt-get update && apt-get install -y curl gcc python3-dev python3-pip zlib1g-dev g++ gnupg unixodbc-dev && \
    curl https://packages.microsoft.com/keys/microsoft.asc | apt-key add - && \
    curl https://packages.microsoft.com/config/debian/10/prod.list > /etc/apt/sources.list.d/mssql-release.list && \
    apt-get update && ACCEPT_EULA=Y apt-get install -y msodbcsql17 && \
    pip3 install --no-cache --upgrade pip grpcio google-api-python-client pyodbc

RUN mkdir -p /proto
COPY proto/*.py /proto/
COPY location_grpc.py /
COPY __main__.py /

CMD [ "python3", "/__main__.py" ] 
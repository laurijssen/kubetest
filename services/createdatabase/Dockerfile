FROM alpine:latest as build
LABEL description="Build database container"

RUN apk update && apk add --no-cache build-base gcc libgcc libtool musl-dev unixodbc-dev

COPY services/createdatabase/*.c /
COPY services/createdatabase/*.h /
RUN gcc -L/usr/lib -o /main *.c -l odbc -O3

FROM alpine:latest as runtime
LABEL description="Run database container"
RUN apk update && apk add --no-cache libstdc++ curl gnupg && \
    curl -O https://download.microsoft.com/download/e/4/e/e4e67866-dffd-428c-aac7-8d28ddafb39b/msodbcsql17_17.6.1.1-1_amd64.apk && \
    curl -O https://download.microsoft.com/download/e/4/e/e4e67866-dffd-428c-aac7-8d28ddafb39b/mssql-tools_17.6.1.1-1_amd64.apk && \
    curl -O https://download.microsoft.com/download/e/4/e/e4e67866-dffd-428c-aac7-8d28ddafb39b/msodbcsql17_17.6.1.1-1_amd64.sig && \
    curl -O https://download.microsoft.com/download/e/4/e/e4e67866-dffd-428c-aac7-8d28ddafb39b/mssql-tools_17.6.1.1-1_amd64.sig && \
    curl https://packages.microsoft.com/keys/microsoft.asc  | gpg --import - && \
    gpg --verify msodbcsql17_17.6.1.1-1_amd64.sig msodbcsql17_17.6.1.1-1_amd64.apk && \
    gpg --verify mssql-tools_17.6.1.1-1_amd64.sig mssql-tools_17.6.1.1-1_amd64.apk && \
    apk add --allow-untrusted msodbcsql17_17.6.1.1-1_amd64.apk && \
    apk add --allow-untrusted mssql-tools_17.6.1.1-1_amd64.apk
COPY --from=build /main /
ENTRYPOINT ["/main"]

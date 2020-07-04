#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "httpheader.h"

HTTPREQUEST *InitHeaders()
{
    HTTPREQUEST *req = malloc(sizeof *req);

    req->size = 1;

    req->body = malloc(1024);
    *req->body = '\0';

    req->cap = 10;
    req->col = malloc(req->cap * sizeof *req->col);

    for (int i = 0; i < req->cap; i++)
    {
        req->col[i] = NULL;
    }
    const char *first = "HTTP/1.1 200 OK\n";
    req->col[0] = malloc(strlen(first) + 1);        
    strcpy(req->col[0], first);

    return req;
}

void DestroyHeaders(HTTPREQUEST *req)
{
    for (int i = 0; i < req->size; i++)
    {
        free(req->col[i]);
    }
    free(req->body);
    free(req);
}

int AddHeader(HTTPREQUEST *req, const char *text)
{
    if (req->size >= req->cap)
    {
        req->cap *= 2;
        char **newCollection = realloc(req->col, req->cap);

        if (newCollection == NULL) return 1;

        req->col = newCollection;

        for (int i = req->size; i < req->cap; i++)
        {
            req->col[i] = NULL;
        }

        req->col[req->size] = malloc(strlen(text) + 1);
        strcpy(req->col[req->size], text);

        req->size++;
    }

    return 0;
}

int SetBody(HTTPREQUEST *req, const char *body)
{
    req->body = malloc(strlen(body) + 1);
    strcpy(req->body, body);
}

void Write(HTTPREQUEST *req, int fd)
{
    size_t size = strlen(req->body);

    char msg[1024];

    sprintf(msg, "Content-Length: %ld\n\n", size);

    AddHeader(req, msg);

    int count = 0;

    for (int i = 0; i < req->size; i++)
    {
        count += strlen(req->col[i]);
    }

    count += strlen(req->body);

    write(fd, msg, count);
}
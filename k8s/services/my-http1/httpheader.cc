#include <cstdlib>
#include <stdio.h>
#include <unistd.h>
#include <cstring>
#include "httpheader.h"

HTTPREQUEST *InitHeaders()
{
    HTTPREQUEST *req = (HTTPREQUEST *)std::malloc(sizeof *req);

    req->size = 0;
    req->bodysize = 1024;
    req->body = (char *)std::malloc(req->bodysize);
    *req->body = '\0';

    req->cap = 10;
    req->col = (char **)std::malloc(req->cap * sizeof *req->col);

    for (int i = 0; i < req->cap; i++)
    {
        req->col[i] = NULL;
    }

    return req;
}

void DestroyHeaders(HTTPREQUEST *req)
{
    for (int i = 0; i < req->size; i++)
    {
        std::free(req->col[i]);
    }
    std::free(req->body);
    std::free(req);
}

int AddHeader(HTTPREQUEST *req, const char *text)
{
    if (req->size >= req->cap)
    {
        req->cap *= 2;
        char **newCollection = (char **)std::realloc(req->col, req->cap);

        if (newCollection == NULL) return 1;

        req->col = newCollection;

        for (int i = req->size; i < req->cap; i++)
        {
            req->col[i] = NULL;
        }
    }

    req->col[req->size] = (char *)std::malloc(strlen(text) + 1);
    strcpy(req->col[req->size], text);

    req->size++;

    return 0;
}

int SetBody(HTTPREQUEST *req, const char *body)
{
    size_t size = std::strlen(body) + 1;

    if (size > req->bodysize) 
    {
        free(req->body);
        req->body = (char *)std::malloc(size);
        req->bodysize;
    }

    strcpy(req->body, body);

    return 0;
}

void Write(HTTPREQUEST *req, int fd)
{
    size_t size = strlen(req->body);

    char msg[1024];

    sprintf(msg, "Content-Length: %ld\n", size);

    AddHeader(req, msg);

    int count = 0;

    for (int i = 0; i < req->size; i++)
    {
        count += strlen(req->col[i]);
    }

    count += strlen(req->body);

    char *buf = (char *)std::malloc(count);
    *buf = '\0';

    for (int i = 0; i < req->size; i++)
    {
        std::strcat(buf, req->col[i]);
    }

    std::strcat(buf, "\n");
    std::strcat(buf, req->body);
    write(fd, buf, count + 1);

    free(buf);
}
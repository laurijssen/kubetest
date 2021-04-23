from threading import Thread
from flask import current_app, render_template
from flask_mail import Message
from . import mail

import json
import  requests, os

def send_async_email(app, msg):
    with app.app_context():
        mail.send(msg)

def send_email(to, subject, template, **kwargs):
    url = os.environ['TRUSTIFI_URL']+'/api/i/v1/email'

    body = render_template(template + '.html', **kwargs)
    body = json.dumps(body)

    payload = f'{{\"recipients\":[{{\"email\":\"{to}\"}}],\"title\":\"{subject}\",\"html\":{body}}}'

    headers = {
    'x-trustifi-key': os.environ['TRUSTIFI_KEY'],
    'x-trustifi-secret': os.environ['TRUSTIFI_SECRET'],
    'Content-Type': 'application/json'
    }

    response = requests.request('POST', url, headers = headers, data = payload)
    print(response.json())


def send_email_gmail(to, subject, template, **kwargs):
    app = current_app._get_current_object()
    msg = Message(app.config['MAIL_SUBJECT_PREFIX'] + ' ' + subject,
                  sender=app.config['MAIL_SENDER'], recipients=[to])
    msg.body = render_template(template + '.txt', **kwargs)
    msg.html = render_template(template + '.html', **kwargs)
    thr = Thread(target=send_async_email, args=[app, msg])
    thr.start()
    return thr
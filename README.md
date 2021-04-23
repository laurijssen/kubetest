from itsdangerous import TimedJSONWebSignatureSerializer as Serializer
s = Serializer(app.config['SECRET_KEY'], expires_in=3600)
token = s.dumps({ 'confirm': 10 })

data = s.loads(token)
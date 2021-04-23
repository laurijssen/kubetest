from flask import jsonify, request, g, url_for, current_app
from .. import db
from ..models import Location
from . import api
from .errors import forbidden

@api.route('/locations/', methods=['POST'])
def new_location():
    loc = Location.query.get(g.current_user.id)

    loc_json = Location.from_json(request.json)

    if loc is None:
        loc = Location(lon=loc_json.lon, lat=loc_json.lat)
        loc.user_id = g.current_user.id
    else:
        loc.lon = loc_json.lon
        loc.lat = loc_json.lat

    db.session.add(loc)
    db.session.commit()
    return jsonify(loc.to_json()), 201, \
        {'Location': url_for('api.get_location', id=loc.user_id)}

@api.route('/locations/<int:id>')
def get_location(id):
    loc = Location.query.get_or_404(id)
    return jsonify(loc.to_json())

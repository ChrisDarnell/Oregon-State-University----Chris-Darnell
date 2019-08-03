#!/usr/bin/env python


# [START imports]
import os
import urllib
import json


from google.appengine.api import users
from google.appengine.ext import ndb


import webapp2


class Boat(ndb.Model):
    id = ndb.StringProperty(indexed = True)
    name = ndb.StringProperty(required = True)
    type = ndb.StringProperty(required = True)
    length = ndb.IntegerProperty(required = True)
    at_sea = ndb.BooleanProperty(required = True,
    default = True)


class Slip(ndb.Model):
    id = ndb.StringProperty(indexed = True)
    number = ndb.IntegerProperty(required = True)
    current_boat = ndb.StringProperty(
    default = 'Empty')
    arrival_date = ndb.DateProperty()


class BoatHandler(webapp2.RequestHandler):
    def post(self, id = None):
        boat_data = json.loads(self.request.body)
        new_boat = Boat(id = boat_data['id'], name = boat_data['name'], type = boat_data['type'], length = boat_data['length'], at_sea = boat_data['at_sea'])
        new_boat.put()
        boat_dict = new_boat.to_dict()
        boat_dict['self'] = '/boat' + new_boat.key.urlsafe()


def get(self, id = None):

    boats = Boat.all()
    data = []

    for boat in boats:
        data.append({
            'id': boat.key().id(),
            'name': boat.name,
            'type': boat.type,
            'length': boat.length,
            'at_sea': boat.at_sea,
        })
    self.response.out.write(json.dumps(data))


def delete(self, id = None):
    self.response.headers['Content-Type'] = 'application/json'
    args = json.loads(self.request.body)
    boat = Boat.get_by_id(args.get('id'))
    boat.delete()
    self.response.out.write('Deleted.')
    slip.current_boat = 'Empty'




def put(self, id = None):
    self.response.headers['Content-Type'] = 'application/json'
    args = json.loads(self.request.body)
    boat = Boat.get_by_id(args.get('id'))
    boat.name = args.get('name')
    boat.type = args.get('type')
    boat.length = args.get('length')
    boat.at_sea = args.get('at_sea')
    self.response.out.write('Added.')



class SlipHandler(webapp2.RequestHandler):
    def post(self, id = None):
        slip_data = json.loads(self.request.body)
        new_slip = Slip(id = slip_data['id'], number = slip_data['number'], current_boat = slip_data['current_boat'], arrival_date = slip_data['arrival_date'])
        new_slip.put()
        slip_dict = new_slip.to_dict()
        slip_dict['self'] = '/slip' + new_slip.key.urlsafe()


def get(self, id = None):
    self.response.headers['Content-Type'] = 'application/json'
    slips = Slip.all()
    data = []
    for slip in slips:
        data.append({
            'id': slip.key().id(),
            'number': slip.number,
            'current_boat': slip.current_boat,
            'arrival_date': slip.arrival_date,
        })
    self.response.out.write(json.dumps(data))


def delete(self, id = None):
    self.response.headers['Content-Type'] = 'application/json'
    args = json.loads(self.request.body)
    slip = Slip.get_by_id(args.get('id'))
    slip.delete()
    self.response.out.write('Deleted.')
    boat.at_sea = True


def put(self, id = None):
    self.response.headers['Content-Type'] = 'application/json'
    args = json.loads(self.request.body)
    slip = Slip.get_by_id(args.get('id'))
    slip.number = args.get('number')
    slip.current_boat = args.get('current_boat')
    slip.arrival_date = args.get('arrival_date')
    self.response.out.write('Added.')



#[START main_page]
class MainPage(webapp2.RequestHandler):

    def get(self):
        self.response.write("Chris Darnell - RESTFUL API Planning and Implementation")




allowed_methods = webapp2.WSGIApplication.allowed_methods
new_allowed_methods = allowed_methods.union(('PATCH', ))
webapp2.WSGIApplication.allowed_methods = new_allowed_methods


#[START app]
app = webapp2.WSGIApplication([
    ('/', MainPage), ('/boat', BoatHandler), ('/boat/(.*)', BoatHandler), ('/slip', SlipHandler), ('/slip/(.*)', SlipHandler),


], debug = True)
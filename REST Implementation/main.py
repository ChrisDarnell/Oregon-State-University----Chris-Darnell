#!/usr/bin/env python


# [START imports]
import os
import urllib
import json


from google.appengine.api import users
from google.appengine.ext import ndb
from google.appengine.ext.db import Key


import webapp2




class Boat(ndb.Model):
    # boat_id = ndb.StringProperty(indexed = True)
    name = ndb.StringProperty(required = True)
    type = ndb.StringProperty(required = True)
    length = ndb.IntegerProperty(required = True)
    at_sea = ndb.BooleanProperty(default = True)




class Slip(ndb.Model):
    # slip_id = ndb.StringProperty(indexed = True)
    number = ndb.StringProperty(required = True)
    current_boat = ndb.StringProperty(default = 'NULL')
    arrival_date = ndb.StringProperty()
    # departure_history= [{departure_date = ndb.DateProperty(), departed_boat = ndb.StringProperty()}]
    departure_date = ndb.StringProperty()
    departed_boat = ndb.StringProperty()




#                 



class BoatHandler(webapp2.RequestHandler):
    def post(self):
        boat_data = json.loads(self.request.body)
        new_boat = Boat(name=boat_data['name'], type=boat_data['type'], length=boat_data['length'], at_sea=boat_data['at_sea'])
        new_boat.put()
        boat_dict = new_boat.to_dict()
        boat_dict['self'] = '/boat/' + new_boat.key.urlsafe()
        self.response.write(json.dumps(boat_dict))

    def get(self, id=None):
        if id:
            b = ndb.Key(urlsafe=id).get()
            b_d = b.to_dict()
            b_d['self'] = '/boat/' + id
            self.response.write(json.dumps(b_d))

    # def delete(self)
    #     if id:
    #         self.delete(id)



   



class SlipHandler(webapp2.RequestHandler):
    def post(self):
        slip_data = json.loads(self.request.body)
        new_slip = Slip(number=slip_data['number'], current_boat=slip_data['current_boat'], arrival_date=slip_data['arrival_date'], 
            departure_date=slip_data['departure_date'], departed_boat=slip_data['departed_boat'])
        new_slip.put()
        slip_dict = new_slip.to_dict()
        slip_dict['self'] = '/slip/' + new_slip.key.urlsafe()
        self.response.write(json.dumps(slip_dict))

    def get(self, id=None):
        if id:
            s = ndb.Key(urlsafe=id).get()
            s_d = s.to_dict()
            s_d['self'] = '/slip/' + id
            self.response.write(json.dumps(s_d))

    # def delete(self, id):
    #      if id:
    #         self.delete(id)
          




#[START main_page]
class MainPage(webapp2.RequestHandler):

    def get(self):
        self.response.write('RESTFUL API Implementation - Chris Darnell\n')



allowed_methods = webapp2.WSGIApplication.allowed_methods
new_allowed_methods = allowed_methods.union(('PATCH', ))
webapp2.WSGIApplication.allowed_methods = new_allowed_methods


#[START app]
app = webapp2.WSGIApplication([
    ('/', MainPage), ('/boat/', BoatHandler), ('/boat/(.*)', BoatHandler), 
    ('/slip/', SlipHandler), ('/slip/(.*)', SlipHandler),


], debug = True)
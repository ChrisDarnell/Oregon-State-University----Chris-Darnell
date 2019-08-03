#!/usr/bin/env python


# [START imports]
import os
import urllib
import json
import requests
from request.auth import HTTPBasicAuth

from google.appengine.api import users
from google.appengine.ext import ndb


import webapp2

db = {}


def _url(path):
    return 'https://localhost:8080' + path


class Boat(ndb.Model):
	id = ndb.StringProperty(indexed=True)
	name =ndb.StringProperty(required=True)
	type = ndb.StringProperty(required=True)
	length = ndb.IntegerProperty(required=True)
	at_sea = ndb.BooleanProperty(required=True, default=False)


class Slip(ndb.Model):
	boat_ref = ndb.StructuredProperty(Boat)
	id = ndb.StringProperty(indexed=True) 
	number = ndb.IntegerProperty(required=True)
	current_boat = ndb.StringProperty(default='')  
	arrival_date = ndb.DateProperty() 


class BoatHandler(webapp2.RequestHandler):
	def post(self):
		boat_data = json.loads(self.request.body)
		new_boat = Boat(id=boat_data['id'], name=boat_data['name'], type=boat_data['type'], length=boat_data['length'], at_sea=boat_data['at_sea'])
		new_boat.put()
		boat_dict = new_boat.to_dict()
		boat_dict['self'] = '/boat' + new_boat.key.urlsafe()
		

	def get(self, id=None):
		# try:

		# 	if id:
		# 		b = ndb.Key(urlsafe=id).get()
		# 		b_d = b.to_dict()
		# 		b_d['self'] = '/boat' + id
		# 		return self.json_response(b_d)

		def get(self, id = None):
        json.loads(self.response.headers)
        boats = Boat.all()
        data = []
        for boat in boats:
            data.append({
                'id': boat.key().id(),
                'name': boat.name,
                'type': boat.type,
                'length': boat.length,
                'at_sea': boat.at-sea,
                })

        self.response.out.write(json.dumps(data))

	

	def delete(self, id):
        if id 
        	b = ndb.Key(urlsafe=id).get()
			b_d = b.to_dict()
			b_d['self'] = '/boat' + id
			ndb.delete 

		def delete(self, id):
        #pop off the script name
        self.request.path_info_pop()
        #forget about the leading '/'
        split = self.request.path_info[1:].split(':')
        db.delete(db.Key.from_path(split[0], int(split[1])))
app = webapp2.WSGIApplication([('/api.*', Rest)], debug=True)



	 def put(self, id):
        try:
            boat_data = Property.objects.get(id=id)
            favorite, create = Favorite.objects.get_or_create(
                    user=self.request.user, property=property)
            if create:
                status = restful.CREATED
            else:
                status = restful.FOUND
            r = self.response(status=status)
            url = favorite.get_absolute_url()
            r['Location'] = self.request.build_absolute_uri(url)
            return r
        except Property.DoesNotExist:
            return self.response(status=restful.NOT_FOUND)
        except Property.MultipleObjectsReturned, e:
          


class SlipHandler(webapp2.RequestHandler):
	def post(self):
		slip_data = json.loads(self.request.body)
		new_slip = Slip(id=slip_data['id'], number=slip_data['number'], current_boat=slip_data['current_boat'], arrival_date=slip_data['arrival_date'])
		new_slip.put()
		slip_dict = new_slip.to_dict()
		slip_dict['self'] = '/slip' + new_slip.key.urlsafe()


	def get(self, id = None):
        json.loads(self.response.headers)
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
        global db

        if(id in db):
            db.pop(id)
            return json.dumps({'Deleted': id})
        else:
            return web.notfound()
	
      def put(self, id)



# [START main_page]
class MainPage(webapp2.RequestHandler):

    def get(self):
       self.response.write("Chris Darnell - RESTFUL API Planning and Implementation")




allowed_methods = webapp2.WSGIApplication.allowed_methods
new_allowed_methods = allowed_methods.union(('PATCH',))
webapp2.WSGIApplication.allowed_methods = new_allowed_methods


# [START app]
app = webapp2.WSGIApplication([
    ('/', MainPage),
    ('/boat', BoatHandler),
    ('/boat/(.*)', BoatHandler),
    ('/slip', SlipHandler),
    ('/slip/(.*)', SlipHandler),


], debug=True)
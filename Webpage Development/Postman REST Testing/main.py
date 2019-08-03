# Chris Darnell
# Assignment 2


from google.appengine.ext import ndb
import webapp2
import json




class Boat(ndb.Model):
	id = ndb.StringProperty()
	name = ndb.StringProperty(required=True)
	boat_type = ndb.StringProperty()
	length = ndb.IntegerProperty()
	at_sea = ndb.BooleanProperty(default=True)

class Slip(ndb.Model):
	id = ndb.StringProperty()
	number = ndb.IntegerProperty(required=True)
	current_boat = ndb.StringProperty()
	arrival_date = ndb.StringProperty()


class BoatHandler(webapp2.RequestHandler):
	def post(self):
		boat_data = json.loads(self.request.body)
		new_boat = Boat(name=boat_data['name'], boat_type=boat_data['boat_type'],length=boat_data['length'], at_sea=True)		
		new_boat.put()
		new_boat.id = new_boat.key.urlsafe()
		boat_dict = new_boat.to_dict()
		boat_dict['self'] = '/boats/' + new_boat.key.urlsafe()
		boat_dict['id'] = new_boat.key.urlsafe()
		self.response.write(json.dumps(boat_dict))

	def get(self, id=None):
		q = Boat.query()
		result = []
		for entry in q:
			dict = {}
			dict['name'] = entry.name
			dict['boat_type'] = entry.boat_type
			dict['length'] = entry.length
			dict['at_sea'] = entry.at_sea
			result.append(dict)
		self.response.write(json.dumps(result))	


	def delete(self, id=None):
		if id:
			b = ndb.Key(urlsafe=id).get()
			if b.at_sea == False:
				q = Slip.query(getattr(Slip, "current_boat") == b.id)
				for entry in q:
					slip_key = entry.id
				s = ndb.Key(urlsafe=slip_key).get()
				s.current_boat = None
				s.put()
			b.key.delete()	


	def patch(self, id=None):
		if id:
			b = ndb.Key(urlsafe=id).get()
			patch_boat_data = json.loads(self.request.body)
			if patch_boat_data['name']:
				b.name = patch_boat_data['name']
			if patch_boat_data['boat_type']:
				b.boat_type = patch_boat_data['boat_type']
			if patch_boat_data['length']:
				b.length = patch_boat_data['length']
			if patch_boat_data['at_sea']:
				b.at_sea = patch_boat_data['at_sea']
				if b.at_sea == True:
					q = Slip.query(getattr(Slip, "current_boat") == b.id)
					for entry in q:
						slip_key = entry.id
					s = ndb.Key(urlsafe=slip_key).get()
					s.current_boat = None
					s.put()
			b.put()
			boat_dict = b.to_dict()
			boat_dict['self'] = '/boats/' + b.key.urlsafe()
			boat_dict['id'] = b.key.urlsafe()
			self.response.write(json.dumps(boat_dict))


class SlipHandler(webapp2.RequestHandler):
	def post(self):
	
		slip_data = json.loads(self.request.body)
		new_slip = Slip(number=slip_data['number'],current_boat=None,arrival_date=slip_data['arrival_date'])
		new_slip.put()
		new_slip.id = new_slip.key.urlsafe()
		new_slip.put()	
		new_slip.id = new_slip.key.urlsafe()
		slip_dict = new_slip.to_dict()
		slip_dict['self'] = '/slips/' + new_slip.key.urlsafe()
		slip_dict['id'] = new_slip.key.urlsafe()
		self.response.write(json.dumps(slip_dict))

	def get(self, id=None):
	
		if id:
			s = ndb.Key(urlsafe=id).get()
			s_d = s.to_dict()
			s_d['self'] = "/slips/" + id
			self.response.write(json.dumps(s_d))
		else:
			q = Slip.query()
			result = []
			for entry in q:
				dict = {}
				dict['number'] = entry.number
				dict['current_boat'] = entry.current_boat
				dict['arrival_date'] = entry.arrival_date
				dict['id'] = entry.id
				result.append(dict)
			self.response.write(json.dumps(result))

	def delete(Self, id=None):
		if id:
			s = ndb.Key(urlsafe=id).get()
			if s.current_boat:
				q = Boat.query(getattr(Boat, "id") == s.current_boat)
				for entry in q:
					boat_key = entry.id
				b = ndb.Key(urlsafe=boat_key).get()
				b.at_sea = True
				b.put()
			s.key.delete()

	def patch(self, id=None):
		if id:
			s = ndb.Key(urlsafe=id).get()
			patch_slip_data = json.loads(self.request.body)
			if patch_slip_data['number']:
				s.number = patch_slip_data['number']
			if patch_slip_data['current_boat']:
				s.current_boat = patch_slip_data['current_boat']
			if patch_slip_data['arrival_date']:
				s.arrival_date = patch_slip_data['arrival_date']
			s.put()
			slip_dict = s.to_dict()
			slip_dict['self'] = '/boats/' + s.key.urlsafe()
			slip_dict['id'] = s.key.urlsafe()
			self.response.write(json.dumps(slip_dict))	

	def put(self, id=None):
		if id:
			s = ndb.Key(urlsafe=id).get()
			patch_slip_data = json.loads(self.request.body)
			s.number = patch_slip_data['number']	
			if patch_slip_data['current_boat']:
				s.current_boat = patch_slip_data['current_boat']
			else:
				s.current_boat = None
			if patch_slip_data['arrival_date']:
				s.arrival_date = patch_slip_data['arrival_date']
			else:
				s.arrival_date = None
			s.id = s.key.urlsafe()				
			s.put()
			slip_dict = s.to_dict()
			slip_dict['self'] = '/boats/' + s.key.urlsafe()
			slip_dict['id'] = s.key.urlsafe()
			self.response.write(json.dumps(slip_dict))


class MainPage(webapp2.RequestHandler):

	def get(self):
		self.response.write("The Marina\n")
		self.response.write("by Chris Darnell")

allowed_methods = webapp2.WSGIApplication.allowed_methods
new_allowed_methods = allowed_methods.union(('PATCH',))
webapp2.WSGIApplication.allowed_methods = new_allowed_methods
app = webapp2.WSGIApplication([
	('/', MainPage),
	('/boats/', BoatHandler),
	('/boats/(.*)', BoatHandler),
	('/slips/', SlipHandler),
	('/slips/(.*)', SlipHandler)

], debug=True)		

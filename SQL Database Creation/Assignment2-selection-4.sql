-- Chris Darnell
-- CS340 - SQL Assignment
-- 2/19/2017


#1 Find all films with maximum length and minimum rental duration (compared to all other films). 
#In other words let L be the maximum film length, and let R be the minimum rental duration in the table film. You need to find all films with length L and rental duration R.
#You just need to return attribute film id for this query. 
SELECT film_id FROM film 
WHERE rental_duration = (
   SELECT MIN(rental_duration) FROM film
) 
AND 
length = (
   SELECT MAX(length) FROM film
);
  

#2 We want to find out how many of each category of film ED CHASE has started in so return a table with category.name and the count
#of the number of films that ED was in which were in that category order by the category name ascending (Your query should return every category even if ED has been in no films in that category).
SELECT c.name AS filmCategory, COUNT(f.name) AS filmCount 
FROM (
   SELECT category.name FROM category
) AS c
LEFT JOIN (
   SELECT category.name FROM category
   INNER JOIN film_category ON film_category.category_id = category.category_id
   INNER JOIN film ON film.film_id = film_category.film_id
   INNER JOIN film_actor ON film.film_id = film_actor.film_id
   INNER JOIN actor ON actor.actor_id = film_actor.actor_id
   WHERE actor.first_name = 'ED' AND actor.last_name = 'CHASE'
) AS f
ON c.name = f.name
GROUP BY c.name
ORDER BY c.name;

#3 Find the first name, last name and total combined film length of Sci-Fi films for every actor
#That is the result should list the names of all of the actors(even if an actor has not been in any Sci-Fi films)and the total length of Sci-Fi films they have been in.
SELECT actor.first_name, actor.last_name, SUM(film.length) FROM actor 
    INNER JOIN film_actor ON film_actor.actor_id = actor.actor_id
        INNER JOIN film ON film.film_id = film_actor.film_id
        GROUP BY actor.first_name, actor.last_name;
 
#4 Find the first name and last name of all actors who have never been in a Sci-Fi film
SELECT actor.first_name, actor.last_name FROM actor
WHERE actor.actor_id NOT IN (
  SELECT DISTINCT actor.actor_id FROM actor
    INNER JOIN film_actor ON film_actor.actor_id = actor.actor_id
    INNER JOIN film_category ON film_category.film_id = film_actor.film_id
    INNER JOIN category ON category.category_id = film_category.category_id
    WHERE category.name = 'Sci-Fi'
);

#5 Find the film title of all films which feature both KIRSTEN PALTROW and WARREN NOLTE
#Order the results by title, descending (use ORDER BY title DESC at the end of the query)
#Warning, this is a tricky one and while the syntax is all things you know, you have to think oustide
#the box a bit to figure out how to get a table that shows pairs of actors in movies
SELECT film.title
FROM film
INNER JOIN film_actor AS first_film_actor
ON first_film_actor.film_id = film.film_id
INNER JOIN actor AS first_actor
ON first_actor.actor_id = first_film_actor.actor_id
INNER JOIN film_actor AS second_film_actor
ON second_film_actor.film_id = film.film_id
INNER JOIN actor as second_actor
ON second_actor.actor_id = second_film_actor.actor_id
WHERE first_actor.first_name = 'KIRSTEN' AND
      first_actor.last_name = 'PALTROW' AND
      second_actor.first_name = 'WARREN' AND
      second_actor.last_name = 'NOLTE'
ORDER BY film.title DESC


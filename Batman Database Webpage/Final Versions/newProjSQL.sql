SET foreign_key_checks = 0;

DROP TABLE IF EXISTS `true_id`;
DROP TABLE IF EXISTS `villain`;
DROP TABLE IF EXISTS `special_abilities`;
DROP TABLE IF EXISTS `true_id_villain`;
DROP TABLE IF EXISTS `true_id_abilities`;
DROP TABLE IF EXISTS `villain_status`;
DROP TABLE IF EXISTS `status`;
DROP TABLE IF EXISTS `creator`;
DROP TABLE IF EXISTS `creator_villain`;



-- create table true_identity
CREATE TABLE true_id (
  id INT(11) PRIMARY KEY AUTO_INCREMENT,
  first_name VARCHAR(255) not null,
  last_name VARCHAR(255) not null,
  status_id int(11) not null,
  foreign key (status_id) references `status` (id),
  unique key(first_name,last_name)
  )
  ENGINE=InnoDB DEFAULT CHARSET=utf8;
  
  -- create table villain
CREATE TABLE villain (
  id INT(11) PRIMARY KEY AUTO_INCREMENT,
  pseudonym VARCHAR(255) NOT NULL,
  creator_id INT(11),
  foreign key (creator_id) REFERENCES `creator` (id),
  unique key(pseudonym)
  )ENGINE=InnoDB DEFAULT CHARSET=utf8;
    
-- create table abilities
CREATE TABLE special_abilities (
  id INT PRIMARY KEY auto_increment,
  name VARCHAR(255) NOT NULL,
  definition VARCHAR(255) NOT NULL, 
  unique key(name, definition)
  ) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- create table true_id_villain
CREATE TABLE true_id_villain(
    true_id int(11) not null,
    villain_id int(11) not null,
    primary key (villain_id, true_id),
    foreign key (villain_id) references `villain` (id),
    foreign key (true_id) references `true_id` (id)
    )
    Engine = innodb;

CREATE TABLE true_id_abilities (
  ability_id int(11) not null,
  true_id int(11) not null,
  primary key (ability_id, true_id),
  foreign key (ability_id) references `special_abilities` (id),
  foreign key (true_id) references `true_id` (id)
  ) engine = innodb;
  
  
 -- create table status
CREATE TABLE status (
  id INT(11) NOT NULL AUTO_INCREMENT,
  description varchar(255),
  PRIMARY KEY (id)
  )ENGINE=InnoDB DEFAULT CHARSET=utf8;
  
CREATE TABLE creator_villain(
  creator_id INT(11) NOT NULL,
  villain_id INT(11) NOT NULL,
  primary key (creator_id, villain_id),
  foreign key (creator_id) references `creator` (id),
  foreign key (villain_id) references `villain` (id)
  ) ENGINE=INNODB;

CREATE TABLE creator (
  id INT(11) NOT NULL AUTO_INCREMENT,
  first_name varchar(255),
  last_name varchar(255),
  dob date,
  PRIMARY KEY (id)
  )ENGINE=INNODB;
  
  



SET foreign_key_checks = 1;


INSERT INTO status (description) 
VALUES
("At large"), 
("Under Investigation"), 
("Dead"), 
("Captured")
;


-- Populate the true_id table


INSERT INTO true_id (first_name, last_name, status_id)
VALUES ("Selina", "Kyle", (SELECT id FROM status WHERE description = "At Large")),
       ("Pamela", "Isley", (SELECT id FROM status WHERE description = "Captured")),
       ("Harvey", "Dent", (SELECT id FROM status WHERE description = "Dead")),
       ("Edward", "Nygma", (SELECT id FROM status WHERE description = "At Large")),
       ("Jaina", "Hudson", (SELECT id FROM status WHERE description = "At Large")),
       ("Harleen", "Quinzel", (SELECT id FROM status WHERE description = "Captured")),
       ("Thomas", "Elliot", (SELECT id FROM status WHERE description = "Under Investigation")),
       ("Arnold", "Wesker", (SELECT id FROM status WHERE description = "At Large")),
       ("Peyton", "Riley", (SELECT id FROM status WHERE description = "At Large")),
       ("Unknown", "Unknown", (SELECT id FROM status WHERE description = "Dead")),
       ("Cyrus", "Gold", (SELECT id FROM status WHERE description = "Dead")),
       ("Roman", "Sionis", (SELECT id FROM status WHERE description = "At Large")),
       ("Jeremiah", "Arkham",(SELECT id FROM status WHERE description = "Captured")),
       ("Lonnie", "Machin",(SELECT id FROM status WHERE description = "Under Investigation")),
       ("Ulysses", "Armstrong",(SELECT id FROM status WHERE description = "Dead")),
       ("Sam", "Young",(SELECT id FROM status WHERE description = "Dead")),
       ("Oswald", "Cobblepot",(SELECT id FROM status WHERE description = "At Large")),
       ("Jonathan", "Crane",(SELECT id FROM status WHERE description = "Captured")),
       ("Jervis", "Tetch",(SELECT id FROM status WHERE description = "At Large")),
       ("Kirk", "Langstrom",(SELECT id FROM status WHERE description = "At Large")),
       ("Jason", "Todd",(SELECT id FROM status WHERE description = "At Large")),
       ("Victor", "Fries",(SELECT id FROM status WHERE description = "Dead")),
       ("Waylon", "Jones",(SELECT id FROM status WHERE description = "Dead")),
       ("Garfield", "Lynns",(SELECT id FROM status WHERE description = "Dead")),
       ("Ted", "Carson",(SELECT id FROM status WHERE description = "Dead")),
       ("Basil", "Karlo",(SELECT id FROM status WHERE description = "Dead")),
       ("Preston", "Payne",(SELECT id FROM status WHERE description = "Dead")),
       ("Peter", "Malley",(SELECT id FROM status WHERE description = "Dead")),
       ("Todd", "Russell",(SELECT id FROM status WHERE description = "Dead")),
       ("Johnny", "Williams",(SELECT id FROM status WHERE description = "Dead")),
       ("Arthur", "Brown",(SELECT id FROM status WHERE description = "Dead")),
       ("Sondra", "Fuller",(SELECT id FROM status WHERE description = "Dead")),
       ("Matt", "Hagen",(SELECT id FROM status WHERE description = "Dead"))
       ;

INSERT INTO creator (first_name, last_name, dob)
VALUES  ("Bob", "Kane", '1915-10-24'),
		("Bill", "Finger", '1914-02-08'),
        ("Robert", "Kanigher", '1915-06-18'),
        ("Sheldon", "Moldoff", '1920-04-14'),
        ("Dick", "Sprang", '1915-07-28'), -- 5
        ("David", "Finch", '1971-07-04'),
        ("Paul", "Jenkins", '1965-12-06'),
        ("Paul", "Dini", '1957-08-07'),
        ("Bruce", "Tim", '1961-02-05'),
        ("Jim", "Lee", '1964-08-11'), -- 10
        ("Jeph", "Loeb", '1958-01-29'),
        ("Don", "Kramer", '1968-08-06'),
        ("Jerry","Robinson", '1922-01-01'),
        ("Tony", "Daniel", NULL),
        ("Chuck","Dixon", '1954-04-14'),  -- 15 
        ("Doug", "Moench", '1948-02-23'),
        ("Graham", "Nolan", '1962-03-12'),
        ("Alfred", "Bester", '1913-12-18'),
        ("Tom", "Mandrake", '1956-05-26'),
        ("Alan", "Grant",  '1949-01-01'),  -- 20
        ("Norm", "Breyfogle", '1960-02-27'),
        ("Lew Sayre", "Schwartz", '1926-07-24'),
        ("Frank", "Robbins", '1917-09-09'),
        ("Neal", "Adams", '1941-06-15'),
        ("Gerry", "Conway", '1952-09-10'),
        ("Gene", "Colan", '1926-09-01');
        

-- Populate villain table

INSERT INTO villain (pseudonym)
VALUES ("Catwoman"),
       ("Poison Ivy"),
       ("Two-Face"),
       ("Riddler"),
       ("White Rabbit"),
       ("Harley Quinn"),
       ("Hush"),
       ("Ventriloquist"),
       ("Joker"), 
       ("Imperceptible Man"), -- 10
       ("Bane"),
       ("Solomon Grundy"),
       ("Black Mask"),
       ("Anarky"),
       ("Penguin"),
       ("Scarecrow"),
       ("Mad Hatter"),
       ("Man-Bat"),
       ("Robin"), 
       ("Red Hood"),
       ("Mr. Freeze"),
       ("Killer Croc"),
       ("Clayface"),
       ("Lady Clay")
       ;


INSERT INTO creator_villain (creator_id, villain_id)
VALUES  (1,1),
		(2,1),
        (3,2),
        (4,2),
        (1,3),
        (2,3),
        (2,4),
        (5,4),
		(6,5),
        (7,5),
        (8,6),
        (9,6),
        (8,7),
        (12,7),
		
        (1,8),
        (2,8),
        (13,8),
        
        (8,9),
        (12,9),
        
        (14,10),
        
        (15,11),
        (16,11),
        (17,11),
        
        (18,12),
        
        (16,13),
        (19,13),
        
        (20,14),
        (21,14),
        
        (1,15),
        (2,15),
        
        (1,16),
        (2,16),
        
        (2,17),
        (22,17),
        
		(23,18),
        (24,18),
        
        (1,19),
        (2,19),
        (13,19),

		(1,20),
		(4,20),

        (25,21),
        (26,21),
        
        (1,22),
        (2,22),
        
        (1,23),
        (2,23);




INSERT INTO special_abilities (name, definition)
VALUES 
      ("Pyrokinesis", "the ability to set objects or people on fire through the concentration of psychic power"),
      ("Immune to Freezing", "resistance to cold and ice"),  
      ("Immune to Fire", "resistance to heat and fire"),
      ("Pharmacology", "the science dealing with the preparation, uses, and especially the effects of drugs"),
      ("Duplication", "to split into two, double"),
      ("Clairvoyance", "the supernatural power of seeing objects or actions removed in space or time from natural viewing"), 
      ("Animal Hybrid", "possessing the abilities of or the ability to change into an animal"), 
      ("Flight", "the act, manner, or power of flying"),
      ("Enhanced Strength", "physical strength significantly above average"),
      ("Enhanced Speed","physical speed significantly above average"), 
      ("Mind Control", "the ability to control another’s thoughts and actions"),
       ("Plant Manipulation", "the ability to control plants and vegetation"),
       ("Invisibility", "to become not visible; not perceptible by the eye"),
       ("Shapeshifting", "the ability to change one’s appearance, size or composition"),
       ("Impersonation", "the act of passing as somebody else"), 
       ("Transmutation", "to change into another nature, substance, form, or condition"),
       ("Enhanced Intellect", "a significantly superior intelligence"),
       ("Combat", "active, armed fighting"), 
       ("Telepathy", "communication between minds by some means other than sensory perception"), 
       ("Telekinesis", "the ability to move or deform inanimate objects through mental processes"),
       ("Magic", "the art of producing a desired effect or result through the use of incantation and control of supernatural agencies or the forces of nature"),
       ("Immune to Poison", "resistance to chemicals and toxins"), 
       ("Electricity", "the ability to control, absorb or create electrical currents"),
       ("Reanimation", "to restore to life; resuscitate"),
       ("Teleportation", "to transport a body across distance psychically"), 
       ("Eidetic Memory", "perfect memory recall"),
       ("Advanced Healing", "the ability to heal wounds at an advanced rate"),
       ("Acrobatics", "remarkable agility"), 
       ("Cyborg", "a person whose physiological functioning is aided by or dependent upon a mechanical or electronic device"),
       ("Superhuman Tracking", "the human ability to track prey through the use of enhanced senses or techniques");




-- Link True ID table to Villain pseudonym


INSERT INTO true_id_villain (true_id, villain_id)
VALUES 
((SELECT id FROM true_id WHERE first_name = "Selina" AND last_name = "Kyle"),
              (SELECT id FROM villain WHERE pseudonym = "Catwoman")),
((SELECT id FROM true_id WHERE first_name = "Pamela" AND last_name = "Isley"),
              (SELECT id FROM villain WHERE pseudonym = "Poison Ivy")),
((SELECT id FROM true_id WHERE first_name = "Harleen" AND last_name = "Quinzel"),
              (SELECT id FROM villain WHERE pseudonym = "Harley Quinn")),
((SELECT id FROM true_id WHERE first_name = "Unknown" AND last_name = "Unknown"),
              (SELECT id FROM villain WHERE pseudonym = "Joker")),
((SELECT id FROM true_id WHERE first_name = "Edward" AND last_name = "Nygma"),
              (SELECT id FROM villain WHERE pseudonym = "Riddler")),
((SELECT id FROM true_id WHERE first_name = "Thomas" AND last_name = "Elliot"),
              (SELECT id FROM villain WHERE pseudonym = "Hush")),
((SELECT id FROM true_id WHERE first_name = "Jaina" AND last_name = "Hudson"),
              (SELECT id FROM villain WHERE pseudonym = "White Rabbit")),
((SELECT id FROM true_id WHERE first_name = "Harvey" AND last_name = "Dent"),
              (SELECT id FROM villain WHERE pseudonym = "Two-Face")),
((SELECT id FROM true_id WHERE first_name = "Victor" AND last_name = "Fries"),
              (SELECT id FROM villain WHERE pseudonym = "Mr. Freeze")),
((SELECT id FROM true_id WHERE first_name = "Jonathan" AND last_name = "Crane"),
              (SELECT id FROM villain WHERE pseudonym = "Scarecrow")),

((SELECT id FROM true_id WHERE first_name = "Unknown" AND last_name = "Unknown"),
             (SELECT id FROM villain WHERE pseudonym = "Imperceptible Man")),
              
((SELECT id FROM true_id WHERE first_name = "Cyrus" AND last_name = "Gold"),
              (SELECT id FROM villain WHERE pseudonym = "Solomon Grundy")),
((SELECT id FROM true_id WHERE first_name = "Jervis" AND last_name = "Tetch"),
              (SELECT id FROM villain WHERE pseudonym = "Mad Hatter")),
((SELECT id FROM true_id WHERE first_name = "Sondra" AND last_name = "Fuller"),
              (SELECT id FROM villain WHERE pseudonym = "Lady Clay")),
((SELECT id FROM true_id WHERE first_name = "Sondra" AND last_name = "Fuller"),
              (SELECT id FROM villain WHERE pseudonym = "Clayface")),
((SELECT id FROM true_id WHERE first_name = "Oswald" AND last_name = "Cobblepot"),
              (SELECT id FROM villain WHERE pseudonym = "Penguin")),
((SELECT id FROM true_id WHERE first_name = "Kirk" AND last_name = "Langstrom"),
              (SELECT id FROM villain WHERE pseudonym = "Man-Bat")),
((SELECT id FROM true_id WHERE first_name = "Arnold" AND last_name = "Wesker"),
              (SELECT id FROM villain WHERE pseudonym = "Ventriloquist")),
((SELECT id FROM true_id WHERE first_name = "Peyton" AND last_name = "Riley"),
              (SELECT id FROM villain WHERE pseudonym = "Ventriloquist")),
((SELECT id FROM true_id WHERE first_name = "Unknown" AND last_name = "Unknown"),
              (SELECT id FROM villain WHERE pseudonym = "Bane")),
((SELECT id FROM true_id WHERE first_name = "Unknown" AND last_name = "Unknown"),
              (SELECT id FROM villain WHERE pseudonym = "Anarky")),
((SELECT id FROM true_id WHERE first_name = "Jason" AND last_name = "Todd"),
              (SELECT id FROM villain WHERE pseudonym = "Robin")),
((SELECT id FROM true_id WHERE first_name = "Jason" AND last_name = "Todd"),
              (SELECT id FROM villain WHERE pseudonym = "Red Hood")),
((SELECT id FROM true_id WHERE first_name = "Matt" AND last_name = "Hagen"),
              (SELECT id FROM villain WHERE pseudonym = "Clayface")),
((SELECT id FROM true_id WHERE first_name = "Basil" AND last_name = "Karlo"),
              (SELECT id FROM villain WHERE pseudonym = "Clayface")),
((SELECT id FROM true_id WHERE first_name = "Preston" AND last_name = "Payne"),
              (SELECT id FROM villain WHERE pseudonym = "Clayface")),
((SELECT id FROM true_id WHERE first_name = "Peter" AND last_name = "Malley"),
              (SELECT id FROM villain WHERE pseudonym = "Clayface")),
((SELECT id FROM true_id WHERE first_name = "Todd" AND last_name = "Russell"),
              (SELECT id FROM villain WHERE pseudonym = "Clayface")),
((SELECT id FROM true_id WHERE first_name = "Johnny" AND last_name = "Williams"),
              (SELECT id FROM villain WHERE pseudonym = "Clayface")),
((SELECT id FROM true_id WHERE first_name = "Arthur" AND last_name = "Brown"),
              (SELECT id FROM villain WHERE pseudonym = "Clayface")),
((SELECT id FROM true_id WHERE first_name = "Jeremiah" AND last_name = "Arkham"),
              (SELECT id FROM villain WHERE pseudonym = "Black Mask")),
((SELECT id FROM true_id WHERE first_name = "Roman" AND last_name = "Sionis"),
              (SELECT id FROM villain WHERE pseudonym = "Black Mask")),
((SELECT id FROM true_id WHERE first_name = "Lonnie" AND last_name = "Machin"),
              (SELECT id FROM villain WHERE pseudonym = "Anarky")),
((SELECT id FROM true_id WHERE first_name = "Ulysses" AND last_name = "Armstrong"),
              (SELECT id FROM villain WHERE pseudonym = "Anarky")),
((SELECT id FROM true_id WHERE first_name = "Sam" AND last_name = "Young"),
              (SELECT id FROM villain WHERE pseudonym = "Anarky"));




-- Link True ID to Special Abilities

INSERT INTO true_id_abilities (true_id, ability_id)
VALUES ((SELECT id FROM true_id WHERE first_name = "Selina" AND last_name = "Kyle"),
              (SELECT id FROM special_abilities WHERE name = "Combat")),
 ((SELECT id FROM true_id WHERE first_name = "Pamela" AND last_name = "Isley"),
              (SELECT id FROM special_abilities WHERE name = "Mind Control")),
 ((SELECT id FROM true_id WHERE first_name = "Pamela" AND last_name = "Isley"),
              (SELECT id FROM special_abilities WHERE name = "Immune to Poison")),
 ((SELECT id FROM true_id WHERE first_name = "Pamela" AND last_name = "Isley"),
              (SELECT id FROM special_abilities WHERE name = "Plant Manipulation")),
 ((SELECT id FROM true_id WHERE first_name = "Harleen" AND last_name = "Quinzel"),
              (SELECT id FROM special_abilities WHERE name = "Acrobatics")),
 ((SELECT id FROM true_id WHERE first_name = "Edward" AND last_name = "Nygma"),
              (SELECT id FROM special_abilities WHERE name = "Enhanced Intellect")),
 ((SELECT id FROM true_id WHERE first_name = "Thomas" AND last_name = "Elliot"),
              (SELECT id FROM special_abilities WHERE name = "Combat")),
 ((SELECT id FROM true_id WHERE first_name = "Jaina" AND last_name = "Hudson"),
              (SELECT id FROM special_abilities WHERE name = "Duplication")),
 ((SELECT id FROM true_id WHERE first_name = "Jaina" AND last_name = "Hudson"),
              (SELECT id FROM special_abilities WHERE name = "Transmutation")),
 ((SELECT id FROM true_id WHERE first_name = "Jaina" AND last_name = "Hudson"),
              (SELECT id FROM special_abilities WHERE name = "Enhanced Speed")),
 ((SELECT id FROM true_id WHERE first_name = "Harvey" AND last_name = "Dent"),
              (SELECT id FROM special_abilities WHERE name = "Combat")),
 ((SELECT id FROM true_id WHERE first_name = "Victor" AND last_name = "Fries"),
              (SELECT id FROM special_abilities WHERE name = "Immune to Freezing")),
 ((SELECT id FROM true_id WHERE first_name = "Victor" AND last_name = "Fries"),
              (SELECT id FROM special_abilities WHERE name = "Reanimation")),
 ((SELECT id FROM true_id WHERE first_name = "Jonathan" AND last_name = "Crane"),
              (SELECT id FROM special_abilities WHERE name = "Immune to Poison")),
 ((SELECT id FROM true_id WHERE first_name = "Jonathan" AND last_name = "Crane"),
              (SELECT id FROM special_abilities WHERE name = "Pharmacology")),
 ((SELECT id FROM true_id WHERE first_name = "Cyrus" AND last_name = "Gold"),
              (SELECT id FROM special_abilities WHERE name = "Reanimation")),
 ((SELECT id FROM true_id WHERE first_name = "Jervis" AND last_name = "Tetch"),
              (SELECT id FROM special_abilities WHERE name = "Mind Control")),
 ((SELECT id FROM true_id WHERE first_name = "Sondra" AND last_name = "Fuller"),
              (SELECT id FROM special_abilities WHERE name = "Shapeshifting")),
 ((SELECT id FROM true_id WHERE first_name = "Oswald" AND last_name = "Cobblepot"),
              (SELECT id FROM special_abilities WHERE name = "Combat")),
 ((SELECT id FROM true_id WHERE first_name = "Kirk" AND last_name = "Langstrom"),
              (SELECT id FROM special_abilities WHERE name = "Flight")),
 ((SELECT id FROM true_id WHERE first_name = "Kirk" AND last_name = "Langstrom"),
              (SELECT id FROM special_abilities WHERE name = "Animal Hybrid")),
 ((SELECT id FROM true_id WHERE first_name = "Arnold" AND last_name = "Wesker"),
              (SELECT id FROM special_abilities WHERE name = "Combat")),
 ((SELECT id FROM true_id WHERE first_name = "Peyton" AND last_name = "Riley"),
              (SELECT id FROM special_abilities WHERE name = "Combat")),
 ((SELECT id FROM true_id WHERE first_name = "Jason" AND last_name = "Todd"),
              (SELECT id FROM special_abilities WHERE name = "Combat")),
 ((SELECT id FROM true_id WHERE first_name = "Matt" AND last_name = "Hagen"),
              (SELECT id FROM special_abilities WHERE name = "Shapeshifting")),
 ((SELECT id FROM true_id WHERE first_name = "Matt" AND last_name = "Hagen"),
              (SELECT id FROM special_abilities WHERE name = "Impersonation")),
 ((SELECT id FROM true_id WHERE first_name = "Basil" AND last_name = "Karlo"),
           (SELECT id FROM special_abilities WHERE name = "Shapeshifting")),
 ((SELECT id FROM true_id WHERE first_name = "Preston" AND last_name = "Payne"),
                  (SELECT id FROM special_abilities WHERE name = "Shapeshifting")),
 ((SELECT id FROM true_id WHERE first_name = "Peter" AND last_name = "Malley"),
                  (SELECT id FROM special_abilities WHERE name = "Shapeshifting")),
 ((SELECT id FROM true_id WHERE first_name = "Todd" AND last_name = "Russell"),
      (SELECT id FROM special_abilities WHERE name = "Shapeshifting")),
 ((SELECT id FROM true_id WHERE first_name = "Johnny" AND last_name = "Williams"),
                   (SELECT id FROM special_abilities WHERE name = "Shapeshifting")),
 ((SELECT id FROM true_id WHERE first_name = "Arthur" AND last_name = "Brown"),
               (SELECT id FROM special_abilities WHERE name = "Shapeshifting")),
 ((SELECT id FROM true_id WHERE first_name = "Jeremiah" AND last_name = "Arkham"),
                  (SELECT id FROM special_abilities WHERE name = "Combat")),
 ((SELECT id FROM true_id WHERE first_name = "Roman" AND last_name = "Sionis"),
               (SELECT id FROM special_abilities WHERE name = "Combat")),
 ((SELECT id FROM true_id WHERE first_name = "Lonnie" AND last_name = "Machin"),
                   (SELECT id FROM special_abilities WHERE name = "Shapeshifting")),
 ((SELECT id FROM true_id WHERE first_name = "Ulysses" AND last_name = "Armstrong"),
                  (SELECT id FROM special_abilities WHERE name = "Combat")),
 ((SELECT id FROM true_id WHERE first_name = "Sam" AND last_name = "Young"),
                    (SELECT id FROM special_abilities WHERE name = "Combat"));


-- what villain is really Roman Sionis?
select pseudonym from villain v inner join
true_id_villain tv on v.id = tv.villain_id inner join
true_id t on t.id = tv.true_id
where t.first_name = "Roman" and last_name = "Sionis";

-- who all has taken on the identity of Anarky?
select first_name, last_name from true_id t inner join
true_id_villain tv on tv.true_id = t.id inner join
villain v on v.id = tv.villain_id
where v.pseudonym = "Anarky"
group by first_name;

-- all dead people
select first_name, last_name from true_id t inner join 
status s on s.id = t.status_id
where s.description = "At Large"
group by t.first_name;

-- all dead people
select first_name, last_name from true_id t inner join 
status s on s.id = t.status_id
where s.description = "Dead"
group by t.first_name;

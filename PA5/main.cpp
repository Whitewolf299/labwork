#include "Actor.h"
#include "Movie.h"
#include "StringSplitter.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;

int main(void)
{
	unordered_map<string, int> has_seen{};

	//grab a file name to open from the user
	string file_name;
	cout << "Enter file name: ";
	getline(cin, file_name);

	//each HT represents the SAME graph.  It just allows for
	//different entry points into the graph
	unordered_map<string, Actor*> all_actors{};
	unordered_map<string, Movie*> all_movies{};

	//open up the file, turn into a graph
	ifstream graph_file{ file_name };
	if (graph_file.is_open() == true)
	{
		//skip first line in file
		string line;
		getline(graph_file, line);

		//next, read rest of data
		while (graph_file.good() == true)
		{
			//grab raw line from our file
			getline(graph_file, line);

			//convert from raw line into cells in our "spreadsheet"
			vector<string> pieces =
				StringSplitter::split(line, "\t");

			//[0] - actor ID
			//[1] - actor name
			//[5] - actor movies (in CSV format)
			string actor_id = pieces[0];
			string actor_name = pieces[1];
			vector<string> movie_ids =
				StringSplitter::split(pieces[5], ",");

			//object to represent this actor
			Actor* some_actor = nullptr;

			//check the grap to see if this actor already exists
			//If it does, grab a pointer to that actor, otherwise,
			//create a new actor and attach to the graph
			if (all_actors.find(actor_id) == all_actors.end())
			{
				some_actor = new Actor{};
				some_actor->setName(actor_name);
				some_actor->setId(actor_id);

				//this line attaches the actor to the graph
				all_actors[some_actor->getId()] = some_actor;
			}

			//repopulate some_actor
			some_actor = all_actors[actor_id];

			//attach movies to actors and actors to movies
			for (auto movie_id : movie_ids)
			{
				//same thing as above.  Check graph to see if movie
				//doesn't exist in our graph.  If it doesn't, make
				//one, then attach the actor to the movie and the
				//movie to the actor.
				Movie* some_movie = nullptr;
				if (all_movies.find(movie_id) == all_movies.end())
				{
					some_movie = new Movie{};
					some_movie->setId(movie_id);
					all_movies[some_movie->getId()] = some_movie;
				}
				some_movie = all_movies[movie_id];
				
				//finally, connect actors to movies and movies to actors
				some_actor->addMovie(some_movie);
				some_movie->addActor(some_actor);
			}
		}
	}
	
	string cin_actor_id;
	int I = 0;
	cout << " Please enter an actor ID (for example nm0000010 ): ";
	getline(cin, cin_actor_id);
	cout << endl << "Name : " << all_actors[cin_actor_id]->getName() << endl;
	vector<Movie*> Movies = all_actors[cin_actor_id]->getMovies();
	cout << "Movie ID's : ";
	for (auto items : Movies)
	{
		cout << Movies[I]->getId() << ",";
		I++;
	}
	cout << endl;
	string repeat, actor_id_1, actor_id_2;
	cout << " Would you like to connect to actors (yes/no): ";
	getline(cin, repeat);

	queue<string> connection;
	queue<int> degrees_queue;
	int degree, is_connected = 0, current_degree;
	string current_id;
	vector<Movie*> actors_movies;
	vector<Actor*> movies_actors;


	while (repeat == "yes")
	{
		cout <<endl << " what is the first actors Id : ";
			getline(cin, actor_id_1);
		cout << endl << " What is the second actors Id : ";
		getline(cin, actor_id_2);
		connection.push(actor_id_1);
		degrees_queue.push(0);
		is_connected = 0;
		while (connection.empty() == false)
		{


			if (current_id == actor_id_2)
			{
				is_connected = 1;
				while (connection.empty() == false)
				{
					connection.pop();
					degrees_queue.pop();
				}
			}
			else
			{

				current_id = connection.front();
				current_degree = degrees_queue.front();

				 connection.pop();
				 degrees_queue.pop();				
				
				
				while (has_seen.count(current_id) == 1 && connection.size() > 0)
				{
					current_id = connection.front();
					current_degree = degrees_queue.front();

					connection.pop();
					degrees_queue.pop();

				}


				 int i = 0;
				actors_movies = all_actors[current_id]->getMovies();
				for(auto items : actors_movies)
				{
					movies_actors = actors_movies[i]->getActors();
					int x = 0;
					for (auto items : movies_actors)
					{
						if (has_seen.count(current_id) != 1)
						{
							connection.push(movies_actors[x]->getId());
							degrees_queue.push(current_degree + 1);
						}
						x++;
					}
					i++;
				}

			}
			has_seen[current_id] = 1;

		}
		if (is_connected == 1)
		{
			cout << "yes These two actors are connected by " << current_degree << " degrees" << endl;
		}
		else
		{
			cout << "no these actors are not connected" << endl;

		}
	
		cout << "Would you like to try two different actors (yes/no): ";
			getline(cin, repeat);
			cout << endl;
	}

	cout << "Would you like to connect two actors with a set degree of distance (yes/no)";
	getline(cin, repeat);

		while (repeat == "yes")
	{
			is_connected = 0;
		cout << " what is the first actor's Id : ";
			getline(cin, actor_id_1);
		cout << endl << " What is the second actor's Id : ";
		getline(cin, actor_id_2);
		cout << endl << "Great what is the degree of distance : ";
		int input_degree;
		cin >> input_degree;
		connection.push(actor_id_1);
		degrees_queue.push(0);

		for(int f = 0 ;f < input_degree ; f++ )
		{


			if (current_id == actor_id_2)
			{
				is_connected = 1;
				while (connection.empty() == false)
				{
					connection.pop();
					degrees_queue.pop();
				}
			}
			else 
				if(connection.size() > 0)
			{

				current_id = connection.front();
				current_degree = degrees_queue.front();

				 connection.pop();
				 degrees_queue.pop();				
				
				
				while (has_seen.count(current_id) == 1 && connection.size() > 0)
				{
					current_id = connection.front();
					current_degree = degrees_queue.front();

					connection.pop();
					degrees_queue.pop();

				}


				 int i = 0;
				actors_movies = all_actors[current_id]->getMovies();
				for(auto items : actors_movies)
				{
					movies_actors = actors_movies[i]->getActors();
					int x = 0;
					for (auto items : movies_actors)
					{
						if (has_seen.count(current_id) != 1)
						{
							connection.push(movies_actors[x]->getId());
							degrees_queue.push(current_degree + 1);
						}
						x++;
					}
					i++;
				}

			}
			has_seen[current_id] = 1;

		}
		if (is_connected == 1)
		{
			cout << "yes These two actors are connected by " << current_degree << " degrees" << endl;
		}
		else
		{
			cout << "no these actors are not connected within " << input_degree << " degrees " << endl;

		}
	
		cout << "Would you like to try two different actors (yes/no): ";
			getline(cin, repeat);
			cout << endl;
	}



		return 0;
}
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
	cout << "Enter file name(reduced.tsv): ";
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
	cout << " You are about to connect two actors: ";

	queue<string> connection;
	queue<int> degrees_queue;
	int degree, is_connected = 0, current_degree;
	string current_id;
	vector<Movie*> actors_movies;
	vector<Actor*> movies_actors;



		cout << endl << " what is the first actors Id : ";
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
				for (auto items : actors_movies)
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


		cout << endl;
	

	cout << "You will now be connecting two actors with a set degree of distance ";

	
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

		for (int f = 0; f < input_degree; f++)
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
				if (connection.size() > 0)
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
					for (auto items : actors_movies)
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

		cout << endl;
	



		
		string task_5_repeate, new_actor_id, new_degree;
		int int_new_degree = 1, max_degree;
		queue<string> Related_actors;
		vector<Movie*> Related_movies;
		vector<Actor*> Degree_of_actors;
		unordered_map<string, int> Related_actor_degrees, actors_have_seen;
		cout << "you will now be starting associative degrees  ";



			cout << endl << "Enter Actor id: ";
			getline(cin, new_actor_id);
			cout << endl << "Enter Max Degree: ";
			getline(cin, new_degree);
			max_degree = stoi(new_degree) + 1;
		
			// couting the actors name
			cout << endl << "Actor : " << all_actors[new_actor_id]->getName()
				<< endl;


			//getting the first degrees of actors
			actors_have_seen[new_actor_id]++;
			Related_movies = all_actors[new_actor_id]->getMovies();
			for (auto actors : Related_movies)
			{
				Degree_of_actors = all_movies[actors->getId()]->getActors();

				for (auto acts : Degree_of_actors)
				{
					if (actors_have_seen[acts->getId()] < 1)
					{
						actors_have_seen[acts->getId()]++;
						Related_actors.push(acts->getId());
						Related_actor_degrees[acts->getId()] = int_new_degree;
					}
				}
			}

			while (int_new_degree < max_degree)
			{
				if (Related_actors.size() < 1)
				{
					int temp = int_new_degree;
					for (int x = temp; x < max_degree; x++, int_new_degree++)
					{
						cout << "Degree[" << x << "] : NONE* " << endl;
					}
					break;
				}
				cout << endl << "Degree [" << int_new_degree << "] actors : ";
				int_new_degree++;
				while (Related_actor_degrees[Related_actors.front()] < int_new_degree)
				{
					if (Related_actors.size() < 1)
					{
						int temp = int_new_degree;
						for (int x = temp; x < max_degree; x++, int_new_degree++)
						{
							cout << "Degree[" << x << "] : NONE* " << endl;
						}
						break;
					}
					else
					{
						cout << all_actors[Related_actors.front()]->getName() << ", ";
						Related_movies = all_actors[Related_actors.front()]->getMovies();
						actors_have_seen[Related_actors.front()]++;
						Related_actors.pop();
						for (auto actors : Related_movies)
						{
							Degree_of_actors = all_movies[actors->getId()]->getActors();

							for (auto acts : Degree_of_actors)
							{
								if (actors_have_seen[acts->getId()] < 1)
								{
									actors_have_seen[acts->getId()]++;
									Related_actors.push(acts->getId());
									Related_actor_degrees[acts->getId()] = int_new_degree;
								}
							}
						}
					}

					if (Related_actors.size() < 1)
					{
						break;
					}

				}
			}
			cout << endl << endl << "Thankyou for using our service!!!!  Goodbye " << endl;
		
		return 0;
}
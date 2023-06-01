import praw
import pandas as pd
import datetime as dt

#Define user agent
user_agent = "scraper_1.0"

#Create an instance of Reddit class
reddit = praw.Reddit(username="Cambobug",
                     password="hufflepif89",
                     client_id="RDpzdo5cuulGpE_518Ojhg",
                     client_secret="37D_YU-2Ri_PRuyqSAhO57YpMyMCnQ",
                     user_agent=user_agent)

subreddit_name = "AskReddit"
subreddit_instance = reddit.subreddit(subreddit_name) #creates an instance of the AskReddit subreddit

titles=[]
scores=[]
ids=[]

for post in subreddit_instance.top(time_filter="day", limit=5):
    titles.append(post.title)
    scores.append(post.score)
    ids.append(post.id)

topComments = [[]]
for i in range(0, 5):
    post = reddit.submission(ids[i])
    post.comment_sort = "top" #sorts comments in post by "top" instead of default "hot"
    post.comments.replace_more(limit=0) #replaces "Load More Comments" buttons in the comment forest
    #print("********" + titles[i] + "********\n")
    for j in range(0, 10): #loops through top 10 comments
        topComments[i].append(post.comments[j].body) #stores comment in topComments array
        #print("Comment #" + str(j) + "\n")
        #print(post.comments[j].body)
    topComments.append([])
    
date = dt.datetime.now()
#t = "gay"
dateStr = date.strftime("%x")
dateStr = dateStr.replace("/", "-")
dateFile = open(str(dateStr) + ".txt", "w")

for i in range(0, 5):
    dateFile.write("Title: " + titles[i] + " Score: " + str(scores[i]) + " ID: " + str(ids[i]) + "\n")
    dateFile.write("Top Comments:")
    for j in range(0, 10):
        try:
            dateFile.write("Comment " + str(j) + ": " + topComments[i][j] + "\n")
        except:
            dateFile.write("Error: Comment contained an unreadable character!\n")
        
dateFile.close()


    

import praw
import pandas as pd
import datetime as dt

#Define user agent
user_agent = "scraper_1.0"

#Create an instance of Reddit class
reddit = praw.Reddit(username="B L A N K", # reddit username would go here
                     password="B L A N K", #reddit passwork would go here
                     client_id="B L A N K", # client ID
                     client_secret="B L A N K", # client secret
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
    for j in range(0, 10): #loops through top 10 comments
        topComments[i].append(post.comments[j].body) #stores comment in topComments array
    topComments.append([])
    
date = dt.datetime.now()
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

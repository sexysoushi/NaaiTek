﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using WebSocial.Helpers;
using Microsoft.AspNet.Identity;
using Microsoft.AspNet.Identity.EntityFramework;
using WebSocial.DAL;
using WebSocial.Models;
using System.Threading.Tasks;

namespace WebSocial.Controllers
{
    public class HomeController : BaseController
    {

        private GameContext db = new GameContext();

        public async Task<ActionResult> Index()
        {
            string userID = User.Identity.GetUserId();
            ApplicationUser user = db.Users.Find(userID);

            IList<int> tagIDs = (from userToTag in db.UsersTags where (userToTag.UserID == userID) select userToTag.TagID).ToList();
            IQueryable<Tag> tags = (from tag in db.Tags where tagIDs.Contains(tag.ID) select tag);
            ViewBag.UserTags = tags;

            string username = user.UserName;
            UserGraph graph = await UserGraphServices.GetUserGraph(username);
            
            // need to remove one because this dimension contains self user
            int dimension = (graph.nodes.Count - 1);

            ViewBag.Dimension = dimension;

            return View(user);
        }

        public ActionResult About()
        {
            ViewBag.Message = "Your application description page.";

            return View();
        }

        public ActionResult Contact()
        {
            ViewBag.Message = "Your contact page.";

            return View();
        }

        public async Task<ActionResult> Statistics()
        {
            UserDimension users = await UserDimensionServices.GetNetworkDimension();
            ViewBag.Dimension = users.users.Count;

            ViewBag.Users = users.users;

            return View();
        }

        public ActionResult SetCulture(string culture)
        {
            // Validate input
            culture = CultureHelper.GetImplementedCulture(culture);
            // Save culture in a cookie
            HttpCookie cookie = Request.Cookies["_culture"];
            if (cookie != null)
                cookie.Value = culture;   // update cookie value
            else
            {
                cookie = new HttpCookie("_culture");
                cookie.Value = culture;
                cookie.Expires = DateTime.Now.AddYears(1);
            }
            Response.Cookies.Add(cookie);
            return RedirectToAction("Index");
        }
    }
}
'use strict';

// Make navbar transparent when it is on the top
const navbar = document.querySelector('#navbar');
const nabvarHeight = navbar.getBoundingClientRect().height;

document.addEventListener('scroll', () => {
    if(window.scrollY > nabvarHeight) {
        navbar.classList.add('navbar--dark');
    } else {
        navbar.classList.remove('navbar--dark');
    }
});


// Handle scrolling when tapping on the navbar menu
const navbarMenu = document.querySelector('.navbar__menu');
navbarMenu.addEventListener('click', (event) => {
    const link = event.target.dataset.link;
    if(link == null) {
        return;
    }

    navbarMenu.classList.remove('open');


    const scrollTo = document.querySelector(link);
    const overTop = scrollTo.getBoundingClientRect().y;
    const distance = window.pageYOffset + overTop - (nabvarHeight-16); 

    // scrollTo.scrollIntoView();
    scroll({top:distance, behavior: 'smooth'});
});


// Navbar toggle button for small screen
const navbarToggleBtn = document.querySelector('.navbar__toggle-btn');
navbarToggleBtn.addEventListener('click', () => {
    navbarMenu.classList.toggle('open');
});


// Handle click on "contact me"button on home
const contactBtn = document.querySelector('.home__contact');
contactBtn.addEventListener('click', () => {
    scrollIntoView('#contact');
});


// Make home slowly fade to transparent as the window scrolls down
const home = document.querySelector('.home__container');
const homeHeight = home.getBoundingClientRect().height;
document.addEventListener('scroll', () => {
    home.style.opacity = 1 - window.scrollY / homeHeight;
});


// Show "arrow up" button when scroll down
const arrowUp = document.querySelector('.arrow-up');
document.addEventListener('scroll', () => {
    if(window.scrollY > homeHeight / 2) {
        arrowUp.classList.add('visible');
    } else {
        arrowUp.classList.remove('visible');
    }
});

// Handle click on the "arrow up" button
arrowUp.addEventListener('click', () => {
    scrollIntoView('#home');
});


// Projects
const workBtnContainer = document.querySelector('.work__categories');
const projectContainer = document.querySelector('.work__projects');
const projects = document.querySelectorAll('.project');
workBtnContainer.addEventListener('click', (e) => {
    const filter = e.target.dataset.filter || e.target.parentNode.dataset.filter;
    if(filter == null) {
        return;
    }

    // Remove selection from the previous item and select the new one 
    const active = document.querySelector('.category__btn.selected');
    active.classList.remove('selected');
    const target = (e.target.nodeName === 'BUTTON' ? e.target : e.target.parentNode);
    target.classList.add('selected');

    projectContainer.classList.add('anim-out');

    setTimeout( () => {
        projects.forEach((project) => {
            if(filter === '*' || filter === project.dataset.type) {
                project.classList.remove('invisible');
            } else {
                project.classList.add('invisible');
            }
        });

        projectContainer.classList.remove('anim-out');
    }, 300);
});



function scrollIntoView(selector) {
    const scrollTo = document.querySelector(selector);
    scrollTo.scrollIntoView({behavior: 'smooth'});
}


const sectionIds = ['#home', '#about', '#skills', '#work', '#contact'];
const sections = sectionIds.map( id => document.querySelector(id));
const navItems = sectionIds.map( id => document.querySelector(`[data-link='${id}']`) );

const observerOptions = {
    root: null,
    rootMargin:'0px',
    threshold: 0.3
}

const observerCallback = (entries, observer) => {
    entries.forEach(entry => {
        const index = sectionIds.indexOf(`#${entry.target.id}`);
        const navItem = navItems[index];
        if(entry.isIntersecting) {
            navItem.classList.add('activeBtn');
        } else {
            navItem.classList.remove('activeBtn');
        }
    });
}

const observer = new IntersectionObserver(observerCallback, observerOptions);
sections.forEach(section => observer.observe(section));
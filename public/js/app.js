var app = app || {};
(function() {

    app.Todo = Backbone.Model.extend({
        urlRoot: '/todos',

        defaults: {
            text: '',
            due: moment().format('YYYY-MM-DD'),
            status: 0
        },

        changeStatus: function() {
            var newStatus = this.get("status") == 0 ? 1 : 0;
            this.save({ status: newStatus });
        }
    });

    app.TodoCollection = Backbone.Collection.extend({
        model: app.Todo,
        url: "/todos",

        completed: function() {
            return this.where({ status: 1 });
        }
    });

    app.Todos = new app.TodoCollection();

    app.TodoView = Backbone.View.extend({
        //el: $('#todos-container'),
        tagName: 'li',
        template: _.template($("#todo-template").html()),

        events: {
            'click .check': 'changeStatus',
            'click label': 'showEditInput',
            'change .editdue': 'updateText',
            'keypress .edittext': 'updateText'
        },

        initialize: function() {
            this.listenTo(this.model, 'change', this.render);
            this.listenTo(this.model, 'destroy', this.remove);
        },

        render: function() {
            this.$el.html(this.template(this.model.toJSON()));

            if (this.model.get("status") == 1) {
                this.$el.addClass("done");
            } else {
                this.$el.removeClass("done");
            }
            var editDueElement = this.$el.find('.editdue');
            var vm = this;
            this.$el.find('.editdue').datepicker({
                language: 'id',
                autoClose: true,
                onSelect: function(date, dt, inst){
                    vm.model.set({due: date});
                }
            })
            return this;
        },

        changeStatus: function(event) {
            this.model.changeStatus();
        },

        showEditInput: function(event) {
            this.$el.find("label").hide();
            this.$el.find("input").show();
            this.$el.find("edittext").focus();
            var editdue = this.$el.find('.editdue');
        },

        updateText: function(event) {
            var $input = $(event.currentTarget);
            var parent = $input.parent();
            console.log($input.attr('class'));
            if ($input.attr('class') == 'edittext') {
                var text = $input.val().trim();
                var due = parent.find('.editdue').val().trim();
                if (event.which != 13 || text == "") {
                    return;
                }
            } else {
                console.log('ON FIRE!');
                var text = parent.find('.edittext').val().trim();
                var due = $input.val();
            }

            if (text === ""){
                return;
            }

            this.model.save({ text: text, due: due });
            this.$el.find("input").hide();
            this.$el.find("label").show();
        }
    });

    app.AppView = Backbone.View.extend({
        el: '.todoapp',

        events: {
            'keypress #todo-text': 'createTodo',
            'change #todo-due': 'createTodo',
            'click #delete-completed': 'deleteCompleted'
        },

        render: function() {
            $('#todo-due').datepicker({
                language: 'id',
                autoClose: true,
                onSelect: function(date, dt, inst){
                    var due = date;
                    var text = $('#todo-text').val().trim();
                    if (text === "") {
                        return;
                    }
                    app.Todos.create({ text: text, due: due });
                    $("#todo-text").val("");
                    $("#todo-due").val("");
                    inst.clear();
                }
            })
        },

        initialize: function() {
            this.listenTo(app.Todos, 'add', this.addOne);
            this.listenTo(app.Todos, 'all', this.render);
            this.listenTo(app.Todos, 'reset', this.addAll);

            app.Todos.fetch({ reset: true });
        },

        addOne: function(todo) {
            var todoView = new app.TodoView({ model: todo });
            $("ul.todos").prepend(todoView.render().el);
        },

        addAll: function() {
            $("ul.todos").html();
            app.Todos.each(this.addOne, this);
        },

        createTodo: function(event) {
            if ($(event.currentTarget).attr('id') === 'todo-text') {
                if (event.which != 13) {
                    return;
                } else {
                    event.preventDefault();
                }
            }

            var text = $("#todo-text").val().trim();
            var due = $('#todo-due').val();
            if (due === '') {
                due = moment().format('YYYY-MM-DD');
            }

            if (text == "") {
                return;
            }

            app.Todos.create({ text: text, due: due });

            $("#todo-text").val('');
            $("#todo-due").val('');
        },

        deleteCompleted: function() {
            _.invoke(app.Todos.completed(), 'destroy');
        }
    });

    new app.AppView();
})()

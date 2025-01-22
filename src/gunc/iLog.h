#ifndef Gunc_iLog_h
#define Gunc_iLog_h

#include "pp.h"

#include <stdarg.h>
#include <stddef.h>

#define Gunc_LOG_ONE(...) __VA_ARGS__, 0
#define Gunc_LOG_MANY(s, ...) s, Gunc_PP_COUNT_32(__VA_ARGS__), __VA_ARGS__

#define Gunc_iLog_msg(self, type, ...) \
	Gunc_iLog_message(self, \
		__FILE__, \
		__func__, \
		__LINE__, \
		type, \
		Gunc_PP_JOIN_EXEC( \
			Gunc_LOG_, \
			Gunc_PP_ONEMANY_32(__VA_ARGS__) \
		)(__VA_ARGS__) \
	)

#define Gunc_iLog_err(self, ...) \
	Gunc_iLog_msg(self, "ERROR", __VA_ARGS__)
#define Gunc_iLog_TODO(self, ...) \
	Gunc_iLog_msg(self, "TODO", __VA_ARGS__)

#define Gunc_iLog_raw(self, ...) \
	Gunc_iLog_raw_f(self, \
		Gunc_PP_JOIN_EXEC( \
			Gunc_LOG_, \
			Gunc_PP_ONEMANY_32(__VA_ARGS._) \
		)(__VA_ARGS__) \
	)
#define Gunc_iLog_raw_nonull(self, ...) \
	Gunc_iLog_raw_f(self, \
		Gunc_PP_JOIN_EXEC( \
			Gunc_LOG_, \
			Gunc_PP_ONEMANY_32(__VA_ARGS._) \
		)(__VA_ARGS__) \
	)

#define Gunc_iLog_pin(self, type) \
	Gunc_iLog_pin_f(self, __FILE__, __func__, __LINE__, type)


enum Gunc_iLog_error_enum {
	Gunc_iLog_END = -1
	, Gunc_iLog_NULL = -2
	, Gunc_iLog_RETRY = -3
};


struct Gunc_iLog {
	void *core;
	int(*raw)(void *core,
		const char *s,
		int arg_count,
		va_list arg_list
	);
	int(*pin)(void *core,
		const char *file_name,
		const char *function_name,
		int line_number,
		const char *type
	);
};

static inline int Gunc_iLog_raw_f(const struct Gunc_iLog *self, const char *s, int arg_count, ...) {
	if (self == NULL || self->core == NULL || self->raw == NULL || s == NULL) {
		return Gunc_iLog_NULL;
	}
	va_list arg_list;
	va_start(arg_list, arg_count);

	int e = self->raw(self->core, s, arg_count, arg_list);

	va_end(arg_list);
	return e;
}
static inline int Gunc_iLog_raw_nonull_f(const struct Gunc_iLog *self, const char *s, int arg_count, ...) {
	va_list arg_list;
	va_start(arg_list, arg_count);

	int e = self->raw(self->core, s, arg_count, arg_list);

	va_end(arg_list);
	return e;
}

static inline int Gunc_iLog_pin_f(const struct Gunc_iLog *self,
	const char *file_name,
	const char *function_name,
	int line_number,
	const char *type
) {
	if (self == NULL || self->core == NULL || self->pin == NULL
		|| file_name == NULL
		|| function_name == NULL
		|| type == NULL
	) {
		return Gunc_iLog_NULL;
	}
	return self->pin(self->core, file_name, function_name, line_number, type);
}

static inline int Gunc_iLog_message(const struct Gunc_iLog *self,
	const char *file_name,
	const char *function_name,
	int line_number,
	const char *type,
	const char *s,
	int arg_count,
	...
) {
	if (self == NULL || self->core == NULL
		|| file_name == NULL
		|| function_name == NULL
		|| type == NULL
		|| s == NULL

		|| self->pin == NULL
		|| self->raw == NULL
	) {
		return Gunc_iLog_NULL;
	}

	int e = self->pin(self->core, file_name, function_name, line_number, type);
	if (e) {
		return e;
	}

	va_list arg_list;
	va_start(arg_list, arg_count);

	e = self->raw(self->core, s, arg_count, arg_list);
	if (e) {
		goto fin;
	}
	e = self->raw(self->core, "\n", 0, arg_list);
	if (e) {
		goto fin;
	}


	fin:
	va_end(arg_list);
	return e;
}


static inline int Gunc_iLog_init(struct Gunc_iLog *self,
	void *core,
	int(*raw)(void *, const char *, int, va_list),
	int(*pin)(void *, const char *, const char *, int, const char *)
) {
	if (self == NULL || core == NULL || raw == NULL || pin == NULL) {
		return Gunc_iLog_NULL;
	}

	*self = (struct Gunc_iLog) {
		.core = core,
		.raw = raw,
		.pin = pin
	};
	return 0;
}


#endif
